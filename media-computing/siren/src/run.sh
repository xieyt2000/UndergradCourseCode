#!/bin/sh
python main.py
python main.py --task poisson --input_path ../data/starfish.jpg --output_dir ../data/poissson
python main.py --task composition --input_path ../data/gizeh.jpg --output_dir ../data/composite --sidelength=512
python main.py --task inpaint --input_path ../data/flower.jpg --output_dir ../data/inpaint --channels 3