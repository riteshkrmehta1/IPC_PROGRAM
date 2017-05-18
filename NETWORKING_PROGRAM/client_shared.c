/*****************************************************************************************
 *   ***** NOT VALIDATED ****
 * DATE - 07/01/2017
 * Simple program who describe how to write and read on memmory using shared memory 
 * concept....
 * SYSTEM CALL   
 * 1 : int shmget(key_t key, size_t size, int shmflg);
 * 2 : int shmctl(int shmid, int cmd, struct shmid_ds *buf);
 * 3 : void *shmat(int shmid, const void *shmaddr, int shmflg);
 * 4 : int shmdt(const void *shmaddr);
 ******************************************************************************************/
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
int main ()
{
	int segment_id;
	char* shared_memory;
	struct shmid_ds shmbuffer;
	int segment_size;
int time ;
	const int shared_segment_size = 0x6400;

	/* Allocate a shared memory segment. */
	segment_id = shmget (10, shared_segment_size, S_IRUSR | S_IWUSR);

	/* Attach the shared memory segment. */
	//	printf ("shared memory attached at address %p\n", shared_memory);

	/* Determine the segment’s size. */
		shmctl (segment_id, IPC_STAT, &shmbuffer);
	//	segment_size = shmbuffer.shm_segsz;
	//	printf ("segment size: %d\n", segment_size);

	/* Write a string to the shared memory segment. */
	//	sprintf (shared_memory, "Hello, world.");
	shared_memory = (char*) shmat (segment_id,(void*) 0x6000000 , 0);
	while(1)

	{
		time=shmbuffer.shm_atime;
		printf("%d\n",time);
		time=shmbuffer.shm_dtime;
		printf("%d\n",time);
		time=shmbuffer.shm_ctime;
		printf("%d\n",time);


		printf(" %s\n",shared_memory);
		sleep(2);
		/* Detach the shared memory segment. */
		//	shmdt (shared_memory);
	}
	/* Reattach the shared memory segment, at a different address. */
	shared_memory = (char*) shmat (segment_id, (void*) 0x5000000, 0);
	printf ("shared memory reattached at address %p\n", shared_memory);

	/* Print out the string from shared memory. */
	printf ("%s\n", shared_memory);

	/* Detach the shared memory segment. */
	shmdt (shared_memory);
	/* Deallocate the shared memory segment.
	   shmctl (segment_id, IPC_RMID, 0);
	 */
	return 0;
}
