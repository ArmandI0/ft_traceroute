#include "../ft_traceroute.h"


volatile sig_atomic_t g_signal_received = 1;

int main(int ac, char **av)
{
    (void)av;
    if (ac < 2)
    {
        ft_printf_fd(STDOUT_FILENO, "Error : %s ", "USAGE");
        exit(EXIT_FAILURE);
    }
    cmd * command = parseEntry(av);
    void setSignalAction(void);

    while(g_signal_received)
    {
        createAndSendPacket(command);
        sleep(1);
    }
    return 0;
}