import sys
from os import walk, system, popen
from os.path import join, split, splitext
from subprocess import run as subprocess_run
from subprocess import PIPE as subprocess_PIPE
from subprocess import Popen as subprocess_Popen
from subprocess import STDOUT as subprocess_STDOUT
from hashlib import md5
import threading

sys.stdin.reconfigure(encoding="utf-8")
sys.stdout.reconfigure(encoding="utf-8")

splitter = "\\" if sys.platform == "win32" else "/"

RequireOptionDict = {
    ".cpp": "includecpp",
    ".py": "includepy",
    ".tex": "includetex",
    ".vimrc": "includevim",
}


def toLatex(string):
    string = string.replace("_", " ")
    string = string.replace("&", "\\&")
    return string


def replace(string):
    string = string.replace("\\", "/")
    return string

def get_hash(file_path):
    cpp_process = subprocess_run(
        ["cpp", "-dD", "-P", "-fpreprocessed", file_path],
        stdout=subprocess_PIPE,
        stderr=subprocess_PIPE,
        text=True
    )

    if cpp_process.returncode != 0:
        raise RuntimeError(f"cpp failed: {cpp_process.stderr}")

    no_whitespace = ''.join(cpp_process.stdout.split())
    md5_hash = md5(no_whitespace.encode()).hexdigest()

    return md5_hash[:6]


def PrepareFileDict(CurPath):
    FileDict = {}
    for root, _, files in walk(CurPath):
        for filename in files:
            fullpath = join(root, filename)
            name, file_extension = splitext(filename)
            if file_extension not in RequireOptionDict:
                continue
            if fullpath[0:3] == "." + splitter + ".":
                continue
            if root == CurPath:
                continue
            DirName = toLatex(split(root)[-1])
            if DirName not in FileDict:
                FileDict[DirName] = []
            FileDict[DirName].append((file_extension, toLatex(name), replace(fullpath)))
    return FileDict


def cmp(x):
    val = 0
    if x == "Misc":
        val = -1
    return [val, x]

def cmp2(x):
    val = 0
    if x[1] == "Note":
        val = -3
    elif x[1] == "Default Code":
        val = -2
    elif x[1] == "Run":
        val = -1
    return [val, x]

def texCodeGen(out, FileDict, FileList):
    for key in sorted(FileDict.keys(), key=cmp):
        out.write("\\section{" + key + "}\n")
        for file_extension, name, path in sorted(FileDict[key], key=cmp2):
            FileList.append(path)
            hash_value = get_hash(path) if file_extension == ".cpp" else ""
            if file_extension == ".cpp" and hash_value:
                out.write(
                    "  \\includecppwithhash{"
                    + name
                    + "}{"
                    + path
                    + "}{"
                    + hash_value
                    + "}\n"
                )
            else:
                out.write(
                    "  \\"
                    + RequireOptionDict[file_extension]
                    + "{"
                    + name
                    + "}{"
                    + path
                    + "}\n"
                )

def print_progress_bar(progress, width=40):
    """
    以浮點數 progress 顯示進度條，會覆蓋掉同一行。
    progress: 介於 0 到 1 的浮點數
    width: 進度條寬度（格數）
    """
    progress = max(0, min(progress, 1))
    filled = int(width * progress)
    bar = '#' * filled + '-' * (width - filled)
    percent = int(progress * 100)
    sys.stdout.write(f"\r[3] Compiling LaTeX : [{bar}] {percent}%")
    sys.stdout.flush()

def monitor_output(stream, n, first_run, FileList):
    for line in iter(stream.readline, ''):
        line = line.strip()
        while len(FileList) > 0:
            if FileList[-1] in line:
                FileList.pop()
                print_progress_bar((n - len(FileList)) / n / 2 + int(not first_run) * 0.5)
            else:
                break

    stream.close()

def GenerateCodebook(FileList, first_run):
    command = [
        "xelatex", "-interaction=nonstopmode", "-synctex=1", "--extra-mem-bot=10000000", "Codebook.tex"
    ]
    proc = subprocess_Popen(
        command,
        stdout=subprocess_PIPE,
        stderr=subprocess_STDOUT,
        universal_newlines=True,
        bufsize=1,
        encoding='utf-8'
    )

    n = len(FileList)
    FileList.reverse()
    for i in range(n):
        if FileList[i][:2] == "./":
            FileList[i] = FileList[i][2:]

    thread = threading.Thread(target=monitor_output, args=(proc.stdout, n, first_run, FileList))
    thread.start()
    proc.wait()
    thread.join()
    if not first_run:
        print() # New line after the progress bar

if __name__ == "__main__":
    print("[#] Start Processing Code Book List...")
    print("[1] Get Codes...")

    FileDict = PrepareFileDict("./codes")
    
    total_files = 0
    for key in FileDict.keys():
        total_files += len(FileDict[key])
    print("    There are", len(FileDict), "folder"+ "(s)" * min(len(FileDict) - 1, 1) + " and", total_files, "file"+ "(s)" * min(total_files - 1, 1))
    print("[2] Prepare Codes...")
    FileList = list()
    with open("list.tex", "w", encoding="utf-8") as fout:
        texCodeGen(fout, FileDict, FileList)

    GenerateCodebook(FileList[:], True)
    GenerateCodebook(FileList[:], False)
    print("[#] Done!")
    if sys.platform == "win32":
        system("pause")
