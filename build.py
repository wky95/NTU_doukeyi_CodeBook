import sys
from os import walk, system, popen
from os.path import join, split, splitext
import shlex

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

    print("    There are", len(FileDict), "file(s)")
    print("[2] Prepare Codes...")
    with open("list.tex", "w", encoding="utf-8") as fout:
        texCodeGen(fout, FileDict)

    print("[3] Compiling LaTeX...")
    command = "xelatex -quiet -synctex=1 -interaction=nonstopmode --extra-mem-bot=10000000 Codebook.tex > /dev/null 2>&1"
    system(command)
    system(command)
    print("[#] Done!")