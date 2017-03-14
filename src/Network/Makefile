######################################
##			IncludePost.mk			##
######################################
MAKE = make
# c++ 컴파일러 지정
CXX = g++ -std=c++11
# 정적 라이브러리 생성을 유틸리티 지정
AR = ar
# 정적 라이브러리 목차 생성 라이브러리
RANLIB = ranlib
# 기타 명령어 선언
RM = rm
MKDIR = mkdir
 
# RELEASE, DEBUG 버전별 FLAG 지정
# RELEASE 모드 컴파일시 'make RELEASE=1'로 컴파일
ifeq ($(RELEASE), 1)
OBJS_DIR  = $(PROJ_HOME)/Release
DBG_FLAGS = -O2 -DNDEBUG
else
OBJS_DIR  = $(PROJ_HOME)/Debug
DBG_FLAGS = -g -O0 -DDEBUG
endif

# DEPEND 파일명 정의
DEPEND_FILE = $(OBJS_DIR)/Epoll.depend

SRC_DIR = $(PROJ_HOME)/src

# g++ 플래그 지정
BOOSTFLAG = -DBOOST_LOG_DYN_LINK -I/usr/local/boost/include -Wl,-rpath="/usr/local/boost/lib"
CPPFLAGS   = -g -W -Wall $(BOOSTFLAG)

# Target 생성시 링크를 위한 Header 파일들 경로 지정
SYS_INC  = 
USER_INC = -I$(PROJ_HOME)/src/Log -I$(PROJ_HOME)/src/Epoll
INCLUDE  = $(SYS_INC) $(USER_INC)

# Target 생성시 링크를 위한 Library 파일 지정
SYS_LIB  = -L/usr/local/boost/lib -lboost_log -lpthread
LIB_DIRS = $(PROJ_HOME)/lib
LIBS += Log
USER_LIB = -L$(LIB_DIRS) $(LIBS)
ALL_LIB  = $(SYS_LIB) $(USER_LIB)

# 라이브러리 생성정보 선언
LIB_NAME = Epoll
LIB_FULL_NAME = $(LIB_DIRS)/lib$(LIB_NAME).a
LIB_SRCS = Epoll.cpp
LIB_OBJS = $(LIB_SRCS:%.cpp=$(OBJS_DIR)/%.o)

# make할 파일 확장자 지정 매크로
.SUFFIXES : .cpp .o

all : $(LIB_FULL_NAME)

# 라이브러리 생성규칙 선언
$(LIB_FULL_NAME) : $(LIB_OBJS)
	@echo "=============================="
	@echo "Create Library $@ "
	@echo "=============================="
	@test -d $(LIB_DIRS) || $(MKDIR) -p $(LIB_DIRS)
	$(AR) rcv $@ $(LIB_OBJS)
	$(RANLIB) $@

# 확장자 규칙으로 컴파일 옵션 지정
$(OBJS_DIR)/%.o : %.cpp
	@echo "=============================="
	@echo "Compliling $@ "
	@echo "=============================="
	@test -d $(OBJS_DIR) || $(MKDIR) $(OBJS_DIR)
	$(CXX) $(CPPFLAGS) $(DBG_FLAGS) $(INCLUDE) -c $< -o $@

depend :
	@test -d $(OBJS_DIR) || $(MKDIR) $(OBJS_DIR)
	@$(RM) -f $(DEPEND_FILE)
	@for FILE in $(LIB_SRCS:%.cpp=%) $(TARGET_SRCS:%.cpp=%); do \
		$(CXX) -MM -MT $(OBJS_DIR)/$$FILE.o $$FILE.cpp $(CPPFLAGS) $(DBG_FLAGS) $(INCLUDE) >> $(DEPEND_FILE); \
	done

# RELESE 버전 make시 의존성규칙 포함되지 않도록 선언
ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), depend)
ifneq ($(strip $(LIB_SRCS) $(TARGET_SRCS)),)
-include $(DEPEND_FILE)
endif
endif
endif
