"""
run all combination of networks defined in rum_mlp.py
"""
import subprocess

if __name__ == '__main__':
    for drop_rate in [0, 0.2, 0.5, 0.9]:
        for batch_norm in [False, True]:
            print(f"drop rate {drop_rate}, {batch_norm}")
            arg_list = ["python3", "main.py", "--drop_rate", str(drop_rate)]
            if batch_norm:
                arg_list.append("--batch_norm")
            subprocess.run(arg_list)

