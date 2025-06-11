#include "../ft_traceroute.h"

volatile sig_atomic_t g_signal_received = 1;


int main(int ac, char **av)
{
    (void)av;
    if (ac < 2)
    {
        ft_printf_fd(STDOUT_FILENO, "traceroute: missing host operand\n");
        ft_printf_fd(STDOUT_FILENO, "Try 'traceroute --help'\n");
        exit(EXIT_FAILURE);
    }
    cmd	*command = parseEntry(av);

	setSignalAction();
    createSocket(command);
    traceroute(command);
    freeAndExit(command, EXIT_SUCCESS);
    return 0;  
}