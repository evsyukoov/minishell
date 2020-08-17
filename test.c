#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
// // int main(void)
// // {
// //     int ABtoC[2];
// //     pipe(ABtoC);
// // 	fork();
// // 	dup2(ABtoC[1], 1);
// // 	close(ABtoC[0]);
// // 	write(1, "hi", 2);
// // 	char buf[3];
// // 	dup2(ABtoC[0], 0);
// // 	read(0, buf, 3);
// // 	write(1, buf, 3);
// // }

// int main(void)
// {
//     int ABtoC[2];
//     pipe(ABtoC);

//     // if (fork() > 0)
//     // {
//         // Process A
//         // close(ABtoC[0]);
//         dup2(ABtoC[1], 1);
//         // close(ABtoC[1]);     // Close this too!
//         // Process A writing to C
//         for (int i = 0; i < 100; i++)
//         {
//             write(1, "Hi\n", sizeof("Hi\n")-1);
//             // usleep(5000);
//         }
//     // }
//     // else if (fork() > 0)
//     // {
//     //     // Process B
//     //     close(ABtoC[0]);
//     //     dup2(ABtoC[1], 1);
//     //     close(ABtoC[1]);
//     //     // Process B writing to C
//     //     for (int i = 0; i < 100; i++)
//     //     {
//     //         write(1, "Lo\n", sizeof("Lo\n")-1);
//     //         usleep(5000);
//     //     }
//     // }
//     // else
//     // {
//         char buffer[100];
//         ssize_t nbytes;
//         // close(ABtoC[1]);
//         dup2(ABtoC[0], 0);
//         // close(ABtoC[0]);
//         // Process C reading from both A and B
//         while ((nbytes = read(0, buffer, sizeof(buffer))) > 0)
//             write(1, buffer, nbytes);
//     // }
//     return(0);
// }

int main() 
{
//	int id;
  //  id = fork();
    int id1;
    int id2;
	int fd;
	int fd1;
	int fd_buf[2];
	char buf[5];

	fd1 = dup(1);
	pipe(fd_buf);

	fd = open("file", O_WRONLY | O_TRUNC | O_CREAT);
	dup2(fd, 1);
	// dup2(fd, 1);

	write(1, "jop", 3);
	dup2(fd1, 1);
	write(1, "net", 3);

	// read(fd[0], buf, 5);
	// dup2(1, fd[1]);
	// write(fd[1], buf, 3);

	return 0; 
} 