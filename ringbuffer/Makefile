
CC        = $(CROSS_COMPILE)g++

TARGET    = ringbuffer_sampl

SRCS	  = ringbuffer_sampl.cpp
OBJS	  = $(SRCS:%.cpp=%.o)
DEPS	  = $(SRCS:%.cpp=%.d)
INCLUDE_DIRS = .

CFLAGS    = -Wall -O $(addprefix -I,$(INCLUDE_DIRS))
LDFLAGS   = 


all: $(TARGET)

-include $(DEPS)

clean: 
	rm -f $(OBJS) $(DEPS) $(TARGET) *~ 


$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) $(DEBUGS) -o $@ $^ $(LDFLAGS)


.cpp.o:
	$(CC) -c -MMD -MP -o $@ $(CFLAGS) $(DEBUGS) $<

