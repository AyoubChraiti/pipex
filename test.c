/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:20:46 by achraiti          #+#    #+#             */
/*   Updated: 2024/01/28 15:21:04 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main (int ac, char **av, char **env)
{
	 char cmd[] = "/bin/ls";
	 char *const args[] = {"/bin/ls", "-la"};

	 if(execve(cmd,args,env) == -1)
	 {
		 printf("error");
		 exit(1);
	 }
	 printf("hello");
	 while(1)
	 {}
	return 0;
}
