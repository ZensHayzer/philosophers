# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 20:34:23 by ajeanne           #+#    #+#              #
#    Updated: 2023/01/31 17:56:44 by ajeanne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME =		philo

SRCS_DIR = $(shell find srcs -type d)
INC_DIR = includes
OBJS_DIR =	objects
DEPS_DIR =	deps

vpath %.c $(foreach dir, $(SRCS_DIR), $(dir):)

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

SRCS =		main.c			\
			check_entry.c	\
			init.c			\
			routine.c		\
			threads_start.c	\
			utils.c

CC =		clang
CFLAGS =	-Wall -Werror -Wextra -g3
INCLUDES_FLAGS = $(addprefix -I,$(INC_DIR))
DEPS_FLAGS = -MT $@ -MMD -MP -MF $(DEPS_DIR)/$*.d
DEPS =		$(SRCS:%.c=$(DEPS_DIR)/%.d)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compile $(NAME)"
	@-$(CC) $(CFLAGS) $(OBJS) $(INCLUDES_FLAGS) -o $(NAME)
	@echo "========      COMPLETE       ========"

$(OBJS_DIR)/%.o: %.c $(OBJS_DIR) $(DEPS_DIR)
	@echo "Creating $@"
	@-$(CC) $(CFLAGS) $(DEPS_FLAGS) $(INCLUDES_FLAGS) -c $< -o $@

$(DEPS):

$(OBJS_DIR):
	@echo "Creating $@"
	@-mkdir -p $@

$(DEPS_DIR):
	@echo "Creating $@"
	@-mkdir -p $@

.PHONY: clean
clean:
	@echo "Deleting $(OBJS_DIR)"
	@-rm -rf $(OBJS_DIR)
	@echo "Deleting $(DEPS_DIR)"
	@-rm -rf $(DEPS_DIR)
	@echo "========      COMPLETE      ========"

.PHONY: fclean
fclean: clean
	@echo "Deleting $(NAME)"
	@rm -f $(NAME)
	@echo "========    COMPLETE    ========"

.PHONY: re
re: fclean $(NAME)

-include $(DEPS)
