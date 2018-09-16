NAME_SERV = server

NAME_CLIENT = client

CC = clang

CFLAGS = -Wall -Wextra -Werror

MFLAGS = -lft

INCLUDE_DIR = ./includes

DIR_OBJ = ./obj/

DIR_OBJ_SERVER = ./obj/server/

DIR_OBJ_CLIENT = ./obj/client/

DIR_LIB = ./libft/

SRC_DIR = ./srcs/server/

SRC_DIR_CLI = ./srcs/client/

FILES = main.c \
			core_loop.c \
			manage_users.c \
			create_cmd.c \
			manage_recv_cmd.c \
			manage_nick.c \
			manage_reply.c \
			manage_who.c \
			manage_chan.c \
			manage_join.c \
			manage_leave.c \
			manage_msg.c

FILES_CLIENT = main.c \
				core_loop.c \
				manage_connect.c \
				print.c \
				print_msg.c \
				server_cmd.c \
				data_transfert.c \

SRCS = $(addprefix $(SRC_DIR), $(FILES))

SRCS_CLIENT = $(addprefix $(SRC_DIR_CLI), $(FILES_CLIENT))

OBJS = $(patsubst %.c, $(DIR_OBJ_SERVER)%.o, $(FILES))

OBJS_CLIENT = $(patsubst %.c, $(DIR_OBJ_CLIENT)%.o, $(FILES_CLIENT))

DEP_OBJ = src_msg \
			$(OBJS) \
			$(OBJS_CLIENT)

RM = /bin/rm -rf

all: mkdirobj $(DEP_OBJ)
		@ make -C $(DIR_LIB)
		@ /bin/echo -n "Archiving object in $(NAME_SERV):"
		@ $(CC) -o $(NAME_CLIENT) $(OBJS_CLIENT) $(DIR_OBJ_SERVER)create_cmd.o $(MFLAGS) -L $(DIR_LIB) #-fsanitize=address
		@ $(CC) -o $(NAME_SERV) $(OBJS) $(MFLAGS) -L $(DIR_LIB) #-fsanitize=address
		@ echo " \033[32mAll done!\033[0m"

$(DIR_OBJ_SERVER)%.o: $(SRC_DIR)%.c
	@ /bin/echo -n "    $(notdir $@)"
	@ $(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE_DIR)
	@ echo " \033[32mOK\033[0m"

$(DIR_OBJ_CLIENT)%.o: $(SRC_DIR_CLI)%.c
	@ /bin/echo -n "    $(notdir $@)"
	@ $(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE_DIR)
	@ echo " \033[32mOK\033[0m"

mkdirobj:
	@ mkdir -p $(DIR_OBJ)
	@ mkdir -p $(DIR_OBJ_SERVER)
	@ mkdir -p $(DIR_OBJ_CLIENT)

clean:
	@ make clean -C $(DIR_LIB)
	@ /bin/echo -n "Removing object files:"
	@ $(RM) $(DIR_OBJ)
	@ echo " \033[32mdone\033[0m"

fclean: clean
	@ make fclean -C $(DIR_LIB)
	@ /bin/echo -n "Removing library:"
	@ $(RM) $(NAME_SERV)
	@ $(RM) $(NAME_SERV).dSYM
	@ $(RM) $(NAME_CLIENT)
	@ $(RM) $(NAME_CLIENT).dSYM
	@ echo " \033[32mdone\033[0m"

re: fclean all

src_msg:
	@ echo " src files:"

debug: mkdirobj $(OBJS)
		@ make -C $(DIR_LIB)
		@ /bin/echo -n "Archiving object in $(NAME_SERV):"
		@ $(CC) $(CFLAGS) $(SRCS) $(MFLAGS) -I$(INCLUDE_DIR) -o $(NAME_SERV) -L $(DIR_LIB) -g
		@ $(CC) $(CFLAGS) $(SRCS_CLIENT) $(MFLAGS) -I$(INCLUDE_DIR) -o $(NAME_CLIENT) -L $(DIR_LIB) -g
		@ echo " \033[32mAll done!\033[0m"

.PHONY : all clean fclean re mkdirobj src_msg debug