######################################
##			IncludePre.mk			##
######################################
# c++ 컴파일러 지정
CXX = g++
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
DEPEND_FILE = $(OBJS_DIR)/depend_file
LIB_DIRS = $(PROJ_HOME)/lib
