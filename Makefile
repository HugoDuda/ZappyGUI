##
## EPITECH PROJECT, 2025
## B-YEP-400-NCY-4-1-zappy-laszlo.serdet
## File description:
## Makefile
## Author: @lszsrd
##

AR					:=	ar
CXX					:=	g++

LIB					:=	libraries

CFLAGS				+=	-std=c2x -iquote $(INCLUDE) -Wall -Wextra 		\
						-Wundef -Wshadow -Wpointer-arith -Wfloat-equal 	\
						-Winit-self -Waggregate-return -Wwrite-strings	\
						-Wcast-align -Wmissing-field-initializers -fpic \
						-DSOCKET_THRESHOLD=1024 -DSOCKET_READ_SIZE=256	\
						-DWARNINGS_THRESHOLD=10 -O3
CXXFLAGS			+=	-std=c++23 -iquote include/gui -Wall -Wextra -O3 -g
LDFLAGS				+=	-L$(LIB) -Wl,-rpath,$(LIB) -lm					\
						-llogger -lobject -lcontainer
RAYLIBFLAGS			+=  -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

GUI_BINARY			:=	zappy_gui
GUI_SOURCES			:=	$(shell find sources/gui -name "*.cpp")
GUI_OBJECTS			:=	$(GUI_SOURCES:.cpp=.o)

zappy_gui_assets:
ifneq ($(wildcard resources/),)
else
	git clone https://github.com/HugoDuda/zappyResources.git resources
endif

all: zappy_gui_assets $(GUI_BINARY)

$(GUI_BINARY): $(GUI_OBJECTS)
	$(CXX) $(CXXFLAGS) $(GUI_OBJECTS) -o $(GUI_BINARY) $(RAYLIBFLAGS)
	@printf "\e[1;43mSuccessfully built %s\e[0m\n" $(GUI_BINARY)

clean:
	$(RM) $(GUI_OBJECTS)

fclean:	clean
	$(RM) $(GUI_BINARY)

re: fclean all

.PHONY:	all clean fclean re zappy_gui_assets
