import os
import re

assert os.path.exists('./src/predict')

traces_path = './traces/'
testcases = []
for root, _, files in os.walk(traces_path):
    testcases.extend([os.path.join(root, name) for name in files])

pattern = r"\d+\.?\d*"
dmiss = []
tmiss = []
for case in testcases:
    ret = os.popen(f'./src/predict {case}').read()
    print(ret, end='')
    metrics = re.findall(pattern, ret)
    dmiss.append(float(metrics[1]))
    tmiss.append(float(metrics[2]))

print(f"avg dmiss rate {sum(dmiss)/len(dmiss):.2%}\n"
      f"avg tmiss rate {sum(tmiss)/len(tmiss):.2%}")
