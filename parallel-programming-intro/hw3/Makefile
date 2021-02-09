default:mpi_vector_add mpi_prefix_sum mpi_histo_dist mpi_col_multi mpi_mat_mul
mpi_vector_add: mpi_vector_add.c
	mpicc -g -Wall -o mpi_vector_add mpi_vector_add.c -std=c99
mpi_prefix_sum: mpi_prefix_sum.c
	mpicc -g -Wall -o mpi_prefix_sum mpi_prefix_sum.c -std=c99
mpi_histo_dist: mpi_histo_dist.c
	mpicc -g -Wall -o mpi_histo_dist mpi_histo_dist.c -std=c99
mpi_col_multi: mpi_col_multi.cpp
	mpiicc -O3 -std=c++11 mpi_col_multi.cpp -o mpi_col_multi -no-multibyte-chars
mpi_mat_mul: mpi_mat_mul.cpp
	mpiicc -O3 -std=c++11 mpi_mat_mul.cpp -o mpi_mat_mul -no-multibyte-chars
clean: 
	rm -rf ./*.o mpi_vector_add mpi_prefix_sum mpi_histo_dist mpi_col_multi
run_vector_add:
	srun -n 6 -l ./mpi_vector_add
run_prefix_sum:
	srun -n 6 -l ./mpi_prefix_sum
run_histo_dist:
	srun -n 6 -l ./mpi_histo_dist
run_col_multi:
	srun -n 6 -l ./mpi_col_multi 1200
run_mat_mul:
	srun -n 16 -l ./mpi_mat_mul 8000