CFLAGS = -Wall -Wextra -Werror

OBJ_SERVER = server.o help_fc.o ft_printf.o ft_putchar.o ft_putstr.o ft_putnbr.o ft_strchr.o
OBJ_CLIENT = client.o help_fc.o

OBJ_SERVER_BONUS = bonus/server_bonus.o bonus/help_fc_bonus.o bonus/ft_printf_bonus.o \
bonus/ft_putchar_bonus.o bonus/ft_putstr_bonus.o bonus/ft_putnbr_bonus.o bonus/ft_strchr_bonus.o
OBJ_CLIENT_BONUS = bonus/client_bonus.o bonus/help_fc_bonus.o bonus/ft_printf_bonus.o \
bonus/ft_putchar_bonus.o bonus/ft_putstr_bonus.o bonus/ft_putnbr_bonus.o bonus/ft_strchr_bonus.o

all: server client

server : $(OBJ_SERVER)
	cc $(CFLAGS) $(OBJ_SERVER) -o server

client : $(OBJ_CLIENT)
	cc $(CFLAGS) $(OBJ_CLIENT) -o client

bonus: server_bonus client_bonus

server_bonus : $(OBJ_SERVER_BONUS)
	cc $(CFLAGS) $(OBJ_SERVER_BONUS) -o server_bonus

client_bonus : $(OBJ_CLIENT_BONUS)
	cc $(CFLAGS) $(OBJ_CLIENT_BONUS) -o client_bonus

bonus/%.o: bonus/%.c bonus/minitalk_bonus.h bonus/ft_printf_bonus.h
	cc $(CFLAGS) -c $< -o $@

%.o: %.c minitalk.h ft_printf.h
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_CLIENT_BONUS) $(OBJ_SERVER_BONUS) 

fclean: clean
	rm -rf server client server_bonus client_bonus

re: fclean all