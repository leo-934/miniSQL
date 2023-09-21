project('MINISQL', 'CPP',
	version: '0.1', 
	default_options: ['buildtype=debug'],
	default_options : ['cpp_std=c++17']
)

EXEC_NAME = 'minisql'

dependencies = []

srcs = [
	'./main.cpp',
	'./src/app.cpp',
	'./src/buffermanager.cpp',
	'./src/catalogmanager.cpp',
	'./src/datablock.cpp',
	'./src/def.cpp',
	'./src/indexmanager.cpp',
	'./src/recordmanager.cpp',
	'./src/sqlscanner.cpp',
	'./src/writer.cpp',
	'./src/interpreter.cpp'
]

inc_dirs = []

inc_dirs += include_directories('include')


executable(EXEC_NAME, srcs,
    cpp_args: ['-w', '-fcompare-debug-second'],
	dependencies: dependencies,
	include_directories: inc_dirs,
	install: false)
