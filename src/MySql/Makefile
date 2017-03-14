######################################
##			Makefile of MySql		##
######################################

include $(PROJ_HOME)/IncludePre.mk

# TARGET 컴파일에 필요한 라이브러리명 지정
LIB_NAME = MySql
# 라이브러리 생성정보 선언
LIB_SRCS = MySql.cpp
# Target 생성정보 선언
TARGET_SRCS = 

LIBS += -L/usr/lib64/mysql -lmysqlclient -I/usr/include/mysql -L/usr/lib64 -lmysqlcppconn-static -I/usr/include/cppconn

include $(PROJ_HOME)/IncludePost.mk
