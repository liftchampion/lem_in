##**************************************************************************** #
##                                                                             #
##                                                        :::      ::::::::    #
##   Makefile                                           :+:      :+:    :+:    #
##                                                    +:+ +:+         +:+      #
##   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+         #
##                                                +#+#+#+#+#+   +#+            #
##   Created: 2018/10/29 22:33:54 by ggerardy          #+#    #+#              #
##   Updated: 2019/02/17 02:24:28 by rgalyeon         ###   ########.fr        #
##                                                                             #
##**************************************************************************** #

NAME = libft.a
INCS = includes
SRCDIR = .
ADD_FLAGS =
OBJS_DIR = objs
DPDS_DIR = dpds

CC = clang
WFLAGS = -Wall -Wextra -Werror
DFLAGS = -g
SANITIZE_FLAGS = -fsanitize=address -g

#################################--UTILS--######################################

SRCS = $(shell find $(SRCDIR) -name '*.c')
OBJS = $(patsubst $(SRCDIR)/%,$(OBJS_DIR)/%, $(SRCS:%.c=%.o))
SRCDIR_SED = $(shell echo $(SRCDIR) | sed 's/\./\\\./g')
SRCS_DIRS := $(shell find $(SRCDIR) -name '*.c' -exec dirname {} \; | uniq | \
	sed 's/$(SRCDIR_SED)//g' | sed 's/^\///g' | awk 'length($0) > 1')
HEADERS = $(wildcard $(INCS)/*.h)
OBJS_SUBDIRS = $(addprefix $(OBJS_DIR)/, $(SRCS_DIRS))
DPDS_SUBDIRS = $(addprefix $(DPDS_DIR)/, $(SRCS_DIRS))
DPDS = $(addprefix $(DPDS_DIR)/,$(patsubst \
			$(OBJS_DIR)/%.o,$(DPDS_DIR)/%.d,$(OBJS:.o=.d)))
IS_LIB = $(shell echo $(NAME) | grep -E -o '\.a$$' | sed 's/\.//g')
FLAGS =
VALGRIND_ARGS =
DEBUG_MODE = 0
WAS_PRINTED_CMP := 0

# Add it for prevent remaking after clean
#.SECONDARY:

#################################--BUILD--######################################

all: $(NAME)

################################--LINKING--#####################################

$(NAME): $(OBJS_DIR) $(OBJS_SUBDIRS) $(DPDS_SUBDIRS) $(DPDS_DIR) $(OBJS) $(HEADERS)
	@printf "\e[?25h\033[A\033[K\e[?25h\x1B[38;5;30mLinking   $(NAME)...\x1B[0m\n"
# Set flags
	$(eval FLAGS := $(ADD_FLAGS))
	$(eval FLAGS += $(WFLAGS))
# Link as lib/exe
ifeq ($(IS_LIB),a)
		@ar rcs $(NAME) $(OBJS);
		@ranlib $(NAME);
else
		@$(CC) $(FLAGS) -I $(INCS) $(OBJS) -o $(NAME)
endif
	@echo "\x1B[38;5;29mDone      $(NAME)!\x1B[0m"

-include $(DPDS)

#################################--COMPILING--##################################

$(OBJS_DIR)/%.o: $(SRCDIR)/%.c
	@if [ '$(WAS_PRINTED_CMP)' == '0' ]; then \
		printf "\e[?25l\x1B[38;5;31mCompiling $(NAME)...\nCompiling \x1B[0m" \
		$(eval WAS_PRINTED_CMP := 1); \
	else printf "\033[A\033[10C\033[K"; \
	fi
	@echo "\x1B[38;5;105m$(notdir $*.c)\x1B[0m"
# Set flags
	@$(eval FLAGS := $(ADD_FLAGS))
	@$(eval FLAGS += $(WFLAGS))
# Compile
	@$(CC) -c $(FLAGS) -I $(INCS) $(SRCDIR)/$*.c -o $(OBJS_DIR)/$*.o
#Make dependency
	@$(CC) -MM $(FLAGS) -I $(INCS) $(SRCDIR)/$*.c > $(DPDS_DIR)/$*.d
	@mv -f $(DPDS_DIR)/$*.d $(DPDS_DIR)/$*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $(DPDS_DIR)/$*.d.tmp > $(DPDS_DIR)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(DPDS_DIR)/$*.d.tmp | fmt -1 | \
		  sed -e 's/^ *//' -e 's/$$/:/' >> $(DPDS_DIR)/$*.d
	@rm -f $(DPDS_DIR)/$*.d.tmp
	@mv -f $(DPDS_DIR)/$*.d $(DPDS_DIR)/$*.d.tmp
	@echo '$(OBJS_DIR)' | sed 's/$$/\//g' | tr -d '\n' > $(DPDS_DIR)/$*.d
	@cat $(DPDS_DIR)/$*.d.tmp >> $(DPDS_DIR)/$*.d
	@rm -f $(DPDS_DIR)/$*.d.tmp

#################################--CLEAN/RE--###################################

clean:
	@echo "\x1B[38;5;8mDeleting  $(NAME) objects...\x1B[0m"
	@rm -rf $(DPDS_DIR)
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "\x1B[38;5;24mDeleting  $(NAME)...\x1B[0m"
	@rm -f $(NAME)

re: fclean all

###################################--DEBUG--####################################

ifeq (valgrind,$(firstword $(MAKECMDGOALS)))
  VALGRIND_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(VALGRIND_ARGS):;@:)
endif

debug: WFLAGS = $(DFLAGS)
debug: print_debug re

sanitize: WFLAGS = $(SANITIZE_FLAGS)
sanitize: print_sanitize re

valgrind: print_valgrind debug
	 @~/.brew/bin/valgrind --leak-check=full --show-leak-kinds=definite \
	 --dsymutil=yes --track-origins=yes ./$(NAME) $(VALGRIND_ARGS)

norm: print_norm
	@~/Scripts/norm_script.sh $(SRCS) $(HEADERS)

###################################--MK_DIRS--##################################

$(OBJS_SUBDIRS):
	@$(call make-repo)

$(DPDS_SUBDIRS):
	@$(call make-dpd-repo)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(DPDS_DIR):
	@mkdir -p $(DPDS_DIR)

$(DIRS):
	@$(call make-repo)

define make-repo
	for dir in $(SRCS_DIRS); \
	do \
		mkdir -p $(OBJS_DIR)/$$dir; \
	done
endef

define make-dpd-repo
	for dir in $(SRCS_DIRS); \
	do \
		mkdir -p $(DPDS_DIR)/$$dir; \
	done
endef

###################################--PRINTS--###################################

cursor:
	@printf "\e[?25h"

print_compilation:
	@echo "\x1B[38;5;31mCompiling $(NAME)...\x1B[0m"

print_debug:
	@echo "\x1B[38;5;42mDebug mode $(NAME)...\x1B[0m"

print_sanitize:
	@echo "\x1B[38;5;200mSanitize mode $(NAME)...\x1B[0m"

print_valgrind:
	@echo "\x1B[38;5;202mValgrinding $(NAME)...\x1B[0m"

print_norm:
	@echo "\x1B[38;5;202mNorminetting $(NAME)...\x1B[0m"

###################################--ATTRS--####################################
.PHONY: all clean fclean re debug sanitize valgrind
.PRIVATE: SRCS OBJS OBJS_DIR HEADERS FLAGS DFLAGS SANITIZE_FLAGS \
	VALGRIND_ARGS CC
.HIDDEN: SRCS OBJS OBJS_DIR HEADERS FLAGS DFLAGS SANITIZE_FLAGS \
	VALGRIND_ARGS CC print_compilation print_debug print_sanitize print_valgrind

###################################--END--######################################
