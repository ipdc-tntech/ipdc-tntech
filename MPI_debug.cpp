#include<stdio.h>
#include<iostream.h>
#include<cstdlib>
#include<mpi.h>

template <typename T>
int MPI_Debug_print(T* varible, MPI_Comm comm, ofstream outstream= NULL){
		int my_rank;
	int comm_size;
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);
	
	int name_size;
	char comm_name[10] ;
	MPI_Comm_get_name(comm, comm_name, &name_size);
	
	//save default buffer output locations
	std::streambuff* coutbuf = std::cout.rdbuf();
	bool dirty = false;
	
	//adjust output stream buffers
	std::streambuf* buf;
	if(outfile!=NULL){
		try{
			if(outstream.isopen())
			{
				std::cout.rdbuf(outstream);
				dirty = true;
			}
		} 
		catch (...)
		{
			cout<<"ERROR: outfile stream not openned.\n"<<"Defaulting printing to std::out\n";
		}
	}
	
	for(int i=0; i<comm_size; i++)
	{
		if(my_rank == i){
			cout<<" Rank: "<<i<<" on comm: "<< comm_name <<" :: "<< "Value= " << variable <<  std::cout<<"\n\n";
		}			
		MPI_Barrier(comm);
	}
	
}

template <typename T>
int MPI_Debug_print_array(T* buffer, int count, MPI_Comm comm, ofstream outstream= NULL){

	int my_rank;
	int comm_size;
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);
	
	int name_size;
	char comm_name[10] ;
	MPI_Comm_get_name(comm, comm_name, &name_size);
	
	//save default buffer output locations
	std::streambuff* coutbuf = std::cout.rdbuf();
	bool dirty = false;
	
	//adjust output stream buffers
	std::streambuf* buf;
	if(outfile!=NULL){
		try{
			if(outstream.isopen())
			{
				std::cout.rdbuf(outstream);
				dirty = true;
			}
		} 
		catch (...)
		{
			cout<<"ERROR: outfile stream not openned.\n"<<"Defaulting printing to std::out\n";
		}
	}

	//Cycle through ranks in comm and print out the dataset
	for(int i=0; i<comm_size; i++)
	{
		if(my_rank == i){
			cout<<" Rank: "<<i<<" on comm: "<< comm_name << std::endl;
			for(int j=0; j<count; j++){
				std::cout<<buffer[j]<<" ";
			}
			std::cout<<"\n\n";
		}			
		MPI_Barrier(comm);
	}
	
	//reset buffers
	if(dirty){
		std::cout.rdbuf(coutbuff);
	}
	
	return 0;
}

template <typename T>
int MPI_Debug_print_grid_2D(T* buffer, int rows, int columns, int gridtype, MPI_Comm comm, ofstream outstream= NULL){
	int my_rank;
	int comm_size;
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);
	
	int name_size;
	char comm_name[10] ;
	MPI_Comm_get_name(comm, comm_name, &name_size);
	
	//save default buffer output locations
	std::streambuff* coutbuf = std::cout.rdbuf();
	bool dirty = false;
	
	//adjust output stream buffers
	std::streambuf* buf;
	if(outfile!=NULL){
		try{
			if(outstream.isopen())
			{
				std::cout.rdbuf(outstream.rdbuf();
				dirty = true;
			}
		} catch (...){
			cout<<"ERROR: outfile stream not openned.\n"<<"Defaulting printing to std::out\n";
	}
	
	//Cycle through ranks in comm and print out the dataset
	for(int i=0; i<comm_size; i++)
	{
		if(my_rank == i){
			cout<<" Rank: "<<i<<" on comm: "<< comm_name << std::endl;
			//check if grid is setup as double pointer array or as single grid.
			//if dpa walk through dpa
		    if(std::is_pointer<buffer[0]>::value){
				for(int j=0; j<rows; j++){
					for(int k=0; k<columns; k++){
						std::cout<<buffer[j][k]<<" ";
					}
					std::cout<<"\n";
				}
			}
			
			//if single grid loop along grid. 
			else{
				for(int j=0; j<rows; j++){
					for(int k=0; k<columns; k++){
						std::cout<<buffer[j*columns+k]<<" ";
					}
					std::cout<<"\n";
				}
			}
			std::cout<<"\n\n";
		}			
		MPI_Barrier(comm);
	}
	
	//reset buffers
	if(dirty){
		std::cout.rdbuf(coutbuff);
	}
	
	return 0;
}
