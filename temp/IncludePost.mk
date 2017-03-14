######################################
##			IncludePost.mk			##
######################################
MAKE = make

# g++ 플래그 지정
BOOST_FLAG = -DBOOST_LOG_DYN_LINK
CPP_FLAGS   = -g -W -Wall $(BOOST_FLAG)

# Target 생성시 링크를 위한 Header 파일들 경로 지정
SYS_INC  = -I/usr/local/boost_1_63_0
USER_INC = -I$(PROJ_HOME)/src/Log
INCLUDE  = $(SYS_INC) $(USER_INC)

# Target 생성시 링크를 위한 Library 파일 지정
SYS_LIB  = -L/usr/local/boost_1_63_0/bin.v2/libs/log/build/gcc-4.4.7/release/link-static/threading-multi -lboost_log -lpthread
USER_LIB = -L$(LIB_DIRS) $(LIBS)
ALL_LIB  = $(SYS_LIB) $(USER_LIB)

ifneq ($(LIB_NAME),)
# 라이브러리 전체 이름 선언
LIB_FULL_NAME = $(LIB_DIRS)/lib$(LIB_NAME).a

# 라이브러리 생성정보 선언
LIB_OBJS = $(LIB_SRCS:%.cpp=$(OBJS_DIR)/%.o)
endif


# Target 생성정보 선언
TARGET_OBJS = $(TARGET_SRCS:%.cpp=$(OBJS_DIR)/%.o)
TARGET_NAMES = $(TARGET_SRCS:%.cpp=$(OBJS_DIR)/%)

# make할 파일 확장자 지정 매크로
.SUFFIXES : .cpp .o

all : subdirs $(LIB_FULL_NAME) $(TARGET_NAMES)

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
	$(CXX) $(CPP_FLAGS) $(DBG_FLAGS) $(INCLUDE) -c $< -o $@

# Target 파일 생성 규칙 선언
## 생성될 Target 파일이 여러개일경우 사용
# .SECONDEXPENSION:
## 각각의 Target에 해당하눈 .o파일 지정되게끔 지정
# $(TARGET_NAMES) : $$@.o
# 	$(CXX) -o $@ $< $(ALL_LIB) $(INCLUDE)

## 생성될 Target 파일이 하나일경우 사용
$(TARGET_NAMES) : $(TARGET_OBJS)
	@echo "=============================="
	@echo "Create Binary $@ "
	@echo "=============================="
	$(CXX) $< $(ALL_LIB) $(INCLUDE) -o $(TARGET_NAMES)

subdirs :
	@for dir in $(SUB_DIRS) ; do \
		$(MAKE) -C $$dir all; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done

depend :
	@test -d $(OBJS_DIR) || $(MKDIR) $(OBJS_DIR)
	@$(RM) -f $(DEPEND_FILE)
	@for FILE in $(LIB_SRCS:%.cpp=%) $(TARGET_SRCS:%.cpp=%); do \
		$(CXX) -MM -MT $(OBJS_DIR)/$$FILE.o $$FILE.cpp $(CPP_FLAGS) $(DBG_FLAGS) $(INCLUDE) >> $(DEPEND_FILE); \
	done

clean :
	$(RM) -rf $(OBJS_DIR) $(LIB_FULL_NAME)

# RELESE 버전 make시 의존성규칙 포함되지 않도록 선언
ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), depend)
ifneq ($(strip $(LIB_SRCS) $(TARGET_SRCS)),)
-include $(DEPEND_FILE)
endif
endif
endif
