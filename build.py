import sys
from os import walk, system, popen
from os.path import join, split, splitext, dirname, abspath, isfile
import shlex
import subprocess

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

def Windows_WSL_get_hash(file_name): # Runs under WSL
    script_dir = dirname(abspath(__file__))
    safe_path = join(script_dir, file_name)
    if not isfile(safe_path):
        print(f"Error: '{safe_path}' not found.", file=sys.stderr)
        sys.exit(1)
        
    safe_path = safe_path.replace(":\\", "/").replace("\\", "/")
    safe_path = safe_path.split("/")
    safe_path[-1] = '"' + safe_path[-1] + '"'
    safe_path = "/".join(safe_path)
    safe_path = list(safe_path)
    assert(safe_path[0].isalpha())
    assert(safe_path[0].isupper())
    safe_path[0] = safe_path[0].lower()
    safe_path = ("/mnt/") + "".join(safe_path)

    pipeline = (
        f"cat {safe_path} "
        "| cpp -dD -P -fpreprocessed "
        "| tr -d '[:space:]' "
        "| md5sum "
        "| cut -c-6"
    )

    try:
        completed = subprocess.run(
            ["wsl", "bash", "-lc", pipeline],
            check=True,
            capture_output=True,
            text=True,
            encoding="utf-8",     # force UTF-8 decoding
            errors="replace"      # replace any invalid bytes rather than crash
        )
    except subprocess.CalledProcessError as e:
        print("Error running WSL pipeline:", e, file=sys.stderr)
        print("STDOUT:", e.stdout, file=sys.stderr)
        print("STDERR:", e.stderr, file=sys.stderr)
        sys.exit(1)

    return completed.stdout.strip()

def get_hash(file_path):
    if sys.platform == "win32":
        file_path = file_path[2:]
        return Windows_WSL_get_hash(file_path)
    safe_path = shlex.quote(file_path)
    cmd = f"cat {safe_path} | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6"
    return popen(cmd).read().strip()


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
    if x[1] == "Default Code":
        val = -2
    elif x[1] == "Run":
        val = -1
    return [val, x]

def texCodeGen(out, FileDict):
    for key in sorted(FileDict.keys(), key=cmp):
        out.write("\\section{" + key + "}\n")
        for file_extension, name, path in sorted(FileDict[key], key=cmp2):
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


if __name__ == "__main__":
    print("[#] Start Processing Code Book List...")
    print("[1] Get Codes...")

    FileDict = PrepareFileDict("./codes")
    
    total_files = 0
    for key in FileDict.keys():
        total_files += len(FileDict[key])
    print("    There are", len(FileDict), "folder"+ "(s)" * min(len(FileDict) - 1, 1) + " and", total_files, "file"+ "(s)" * min(total_files - 1, 1))
    print("[2] Prepare Codes...")
    with open("list.tex", "w", encoding="utf-8") as fout:
        texCodeGen(fout, FileDict)

    print("[3] Compiling LaTeX...")
    if sys.platform == "win32":
        command = "xelatex -quiet -synctex=1 -interaction=nonstopmode --extra-mem-bot=10000000 Codebook.tex"
    else:
        command = "xelatex -quiet -synctex=1 -interaction=nonstopmode --extra-mem-bot=10000000 Codebook.tex > /dev/null 2>&1"
    system(command)
    system(command)
    print("[#] Done!")
    if sys.platform == "win32":
        system("pause")
