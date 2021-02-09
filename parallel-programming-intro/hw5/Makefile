all: mpi_mat mpi_omp_mat sort

mpi_mat: mpi_mat.cpp
	mpiicc -Ofast -fopenmp -std=c++11 mpi_mat.cpp -o mpi_mat -no-multibyte-chars

mpi_omp_mat: mpi_omp_mat.cpp
	mpiicc -Ofast -fopenmp -std=c++11 mpi_omp_mat.cpp -o mpi_omp_mat -no-multibyte-chars

sort: sort.cpp
	icc -Ofast -fopenmp -std=c++11 sort.cpp -o sort -no-multibyte-chars

run_mat: mpi_omp_mat
	srun -n 16 -l ./mpi_omp_mat 16000 10

run_sort: sort
	./sort 100000 10

clean:
	rm mpi_omp_mat mpi_mat sort