# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/02 11:43:26 by ppaquet           #+#    #+#              #
#    Updated: 2023/08/25 15:21:03 by ppaquet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==================================================================================================|
#                                                                                    VARIABLES     |
#==================================================================================================|

# ---------------------------------------------------------------------------------< EXECUTABLE >---
NAME := philo
NAME_MAJ := PHILO

# -------------------------------------------------------------------------------------< COLORS >---
WTH := \033[0m#         WHITE
GRN := \033[0;32m#      RESET + GREEN
RED := \033[0;31m#      RESET + RED
YEL := \033[0;33m#      RESET + YELLOW
BLU := \033[0;34m#      RESET + PURPLE/BLUE
BLD := \033[1m#         BOLD
MGT := \033[1;35m#      BOLD + MAGENTA
CYA := \033[1;36m#      BOLD + CYAN

ERASE	:=\033[2K
RST		:=\033[0m

UP			:="\033[A"#cursor up
CUT			:="\033[K"#cut line

# ----------------------------------------------------------------------------------< COMPILING >---
CC := gcc
CL := clang
FLAGS := -g -Wall -Werror -Wextra -pthread
SAN := -fsanitize=thread

# --------------------------------------------------------------------------------------< OTHER >---
RM := rm -rf
DIR := mkdir

# ------------------------------------------------------------------------------------< SOURCES >---
SRCS_PATH := srcs/
SRCS_FILES := \
	main.c \
	philo_actions.c \
	philo_allocation.c \
	philo_env_utils.c \
	philo_exit.c \
	philo_launch.c \
	philo_num_utils.c \
	philo_parsing.c \
	philo_string_utils.c \
	philo_time_utils.c \
	philo_utils.c \
	philosopher.c \
	philo_print.c \

SRCS := $(addprefix $(SRCS_PATH), $(SRCS_FILES))

# -----------------------------------------------------------------------------------< INCLUDES >---
INCL_PATH := include/

# -------------------------------------------------------------------------------------< HEADER >---
HEADER_PHILO := -I ./$(INCL_PATH)

# ------------------------------------------------------------------------------------< OBJECTS >---
OBJS_PATH := objs/
OBJS := $(addprefix $(OBJS_PATH), $(SRCS_FILES:.c=.o))

#==================================================================================================|
#                                                                                      RULES       |
#==================================================================================================|

all: $(NAME)

$(NAME): $(OBJS_PATH) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(HEADER_PHILO) -o $@
	@echo "$(GRN)$(BLD)Creating ./$(NAME) executable$(RST)"
	@sleep 1 && printf $(UP)$(CUT)
	@echo "\t\t$(WTH)./$(NAME) executable _________________ $(GRN)$(BLD)[CREATED]"

$(OBJS_PATH)%.o:$(SRCS_PATH)%.c
	@$(CC) $(FLAGS) -o $@ $(HEADER_PHILO) -c $<
	@echo "$(CYA)Compiling $(notdir $@)$(RST)"
	@sleep 0.2 && printf $(UP)$(CUT)

$(OBJS_PATH):
	@$(DIR) $(OBJS_PATH)

clean:
	@$(RM) $(OBJS_PATH)
	@echo "\t\t$(WTH)./$(NAME) objects ____________________ $(RED)$(BLD)[DELETED]"
	
fclean: clean
	@$(RM) $(NAME)
	@echo "\t\t$(WTH)./$(NAME) executable _________________ $(RED)$(BLD)[DELETED]"

re: fclean all

# --------------------------------------------------------------------------------------< UTILS >---
san: fclean $(OBJS_PATH) $(OBJS)
	@$(CL) $(CFLAGS) $(SAN) $(OBJS) $(HEADER_PHILO) -o $(NAME)
	@echo "$(GRN)$(BLD)Creating ./$(NAME) executable FSANITIZE MODE$(RST)"
	@sleep 1 && printf $(UP)$(CUT)
	@echo "\t\t$(WTH)./$(NAME) executable ____FSANITIZE____ $(GRN)$(BLD)[CREATED]"

backup:
	clear
	@echo "\n$(BLD)[BACKING UP $(NAME_MAJ)]\n"
	@tar -czvf $(NAME)_BACKUP_$(shell date +%Y%m%d_%H%M%S).tar.gz ./* > /dev/null 2>&1
	@mv $(NAME)_BACKUP_$(shell date +%Y%m%d_%H%M%S).tar.gz ~/Desktop/
	@sleep 2 && clear
	@echo "\n$(GRN)$(BLD)[$(NAME_MAJ) BACKUP NOW LOCATED ON DESKTOP]\n"

norm:
	clear
	@echo "\n$(GRN)$(BLD)[NORMINETTE - $(NAME_MAJ) SOURCE FILES]$(WTH)"
	@norminette -R CheckForbiddenSourceHeader $(SRCS_PATH) | awk '{ printf("%65s\n", $$0) }'
	@echo "\n$(GRN)$(BLD)[NORMINETTE - INCLUDES]$(WTH)"
	@norminette -R CheckDefine $(INCL_PATH) | awk '{ printf("%65s\n", $$0) }'

help:
	@grep -E '^[a-zA-Z0-9_-]+:.*' Makefile | awk -F ':' '{print $$1}' | awk '{ printf("%65s\n", $$0) }'

.PHONY: all clean fclean re
