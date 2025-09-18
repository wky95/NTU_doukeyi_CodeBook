def get_hash(path):
    from subprocess import run, PIPE
    from hashlib import md5
    
    p = run(
        ["cpp", "-dD", "-P", "-fpreprocessed", path],
        stdout = PIPE,
        stderr = PIPE,
        text = True
    )
    
    if p.returncode != 0: 
        raise RuntimeError(p.stderr)

    s = ''.join(p.stdout.split())
    ret = md5(s.encode()).hexdigest()
    return ret[:6]

print(get_hash("Suffix_Array.cpp"))
