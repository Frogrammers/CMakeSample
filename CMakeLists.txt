cmake_minimum_required(VERSION 3.6)


##### �v���W�F�N�g�ŗL�̐ݒ� #####
# �v���W�F�N�g���̐ݒ�
set(PROJECT_NAME "CMakeSample")

# ����̐ݒ� (CXX/C)
set(LANG "C")

# �ǉ��p�b�P�[�W�̐ݒ�
set(USE_OPENCL FALSE)
set(USE_CUDA FALSE)
set(USE_OPENCV FALSE)

# �f�o�b�O�̐ݒ�
set(DBG_ARGS "\"Hello CMake!\"")
set(DBG_DEBUGGER "WindowsLocalDebugger")
set(DBG_ENV "")

# �\�[�X�̐ݒ�
add_executable(${PROJECT_NAME}
  ./${PROJECT_NAME}/Source.c
  ./${PROJECT_NAME}/Header.h
)


##### �v���W�F�N�g���ʐݒ� #####
# �\�����[�V�����t�@�C�����̎w��
project(${PROJECT_NAME})

# �X�^�[�g�A�b�v�v���W�F�N�g�̐ݒ�i3.6�ȍ~�j
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# �f�o�b�O�ݒ�t�@�C���̐���
set(FILE_DATA [=[
<?xml version="1.0" encoding="utf-8"?>
<Project ToolsVersion="14.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <LocalDebuggerCommandArguments>REPLACE_DBG_ARGS</LocalDebuggerCommandArguments>
    <DebuggerFlavor>REPLACE_DBG_DEBUGGER</DebuggerFlavor>
    <LocalDebuggerEnvironment>REPLACE_DBG_ENV</LocalDebuggerEnvironment>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <LocalDebuggerCommandArguments>REPLACE_DBG_ARGS</LocalDebuggerCommandArguments>
    <DebuggerFlavor>REPLACE_DBG_DEBUGGER</DebuggerFlavor>
    <LocalDebuggerEnvironment>REPLACE_DBG_ENV</LocalDebuggerEnvironment>
  </PropertyGroup>
</Project>
]=])
string(REGEX REPLACE "REPLACE_DBG_ARGS" "${DBG_ARGS}" FILE_DATA "${FILE_DATA}")
string(REGEX REPLACE "REPLACE_DBG_DEBUGGER" "${DBG_DEBUGGER}" FILE_DATA "${FILE_DATA}")
string(REGEX REPLACE "REPLACE_DBG_ENV" "${DBG_ENV}" FILE_DATA "${FILE_DATA}")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.vcxproj.user" "${FILE_DATA}")

# ����̎w��
enable_language(${LANG})

# �R���p�C���o�[�W�����̐ݒ�
if (${LANG} STREQUAL "C")
  set(CMAKE_C_STANDARD 11)    # for C
elseif (${LANG} STREQUAL "CXX")
  set(CMAKE_CXX_STANDARD 11)  # for C++
else ()
endif ()

# �R���p�C���I�v�V�����̎w��
if (${LANG} STREQUAL "C")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /TC /W4")       # for C
elseif (${LANG} STREQUAL "CXX")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /TP /W4 /EHsc") # for C++
else ()
endif ()

# �p�b�P�[�W�̌���
if ((DEFINED USE_OPENCL) AND (${USE_OPENCL}))
  find_package(OpenCL REQUIRED)
endif ()
if ((DEFINED USE_CUDA) AND (${USE_CUDA}))
  find_package(CUDA REQUIRED)
endif ()
if ((DEFINED USE_OPENCV) AND (${USE_OPENCV}))
  find_package(OpenCV REQUIRED)
endif ()

# �p�b�P�[�W�̒ǉ�
if ((DEFINED USE_OPENCL) AND (OpenCL_FOUND))  # OpenCL
  # ���b�Z�[�W�̏o��
  message("OpenCL headers and libraries added.")
  # �C���N���[�h�p�X�̒ǉ�
  include_directories(${OpenCL_INCLUDE_DIRS})
  # �����N�^�[�Q�b�g�̒ǉ�
  target_link_libraries(${PROJECT_NAME} ${OpenCL_LIBRARIES})
endif ()
if ((DEFINED USE_CUDA) AND (CUDA_FOUND))      # CUDA
  # ���b�Z�[�W�̏o��
  message("CUDA headers and libraries added.")
  # �C���N���[�h�p�X�̒ǉ�
  include_directories(${CUDA_INCLUDE_DIRS})
  # �����N�^�[�Q�b�g�̒ǉ�
  target_link_libraries(${PROJECT_NAME} ${CUDA_LIBRARIES})
endif ()
if ((DEFINED USE_OPENCV) AND (OpenCV_FOUND))  # OpenCV
  # ���b�Z�[�W�̏o��
  message("OpenCV headers and libraries added.")
  # �C���N���[�h�p�X�̒ǉ�
  include_directories(${OpenCV_INCLUDE_DIRS})
  # �����N�^�[�Q�b�g�̒ǉ�
  target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
endif ()

# ���̑��C���N���[�h�p�X�̒ǉ�
include_directories(
)

# ���̑������N�^�[�Q�b�g�̒ǉ�
target_link_libraries(${PROJECT_NAME}
)