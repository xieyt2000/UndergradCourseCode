"""
run all combination of networks defined in rum_mlp.py
"""
import subprocess

if __name__ == '__main__':
    LOSSES = ["Euclidean", "Softmax", "Hinge"]
    ACTIVATIONS = ["Relu", "Sigmoid", "Gelu"]
    for layers in range(1, 3):
        for loss in LOSSES:
            for activation in ACTIVATIONS:
                print(f"layers {layers}, loss {loss}, activation {activation}")
                subprocess.run(["python3", "run_mlp.py", "--layers", str(layers),
                                "--loss", loss, "--activation", activation])
