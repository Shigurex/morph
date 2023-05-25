CXX = c++
CXXFLAGS = --std c++20 -MMD -MP

INCLUDES = -I ./includes -I ./darts-clone/include

SRCDIR = srcs
OBJDIR = objs

SRCS = $(shell find $(SRCDIR) -type f -name "*.cpp")
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS = $(OBJDIR)/*.d

NAME = morph

$(NAME): $(OBJDIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

$(OBJDIR):
	mkdir $(shell find $(SRCDIR) -type d | sed 's/^$(SRCDIR)/$(OBJDIR)/g')

all: $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<