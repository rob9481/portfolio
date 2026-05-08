project('starter', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++23'])

# https://mesonbuild.com/Tutorial.html
gtk4_dep = dependency('gtk4')
executable('starter_gtk',
           'main_gtk.cpp',
           dependencies: gtk4_dep)

# https://mesonbuild.com/Qt6-module.html
qt6 = import('qt6')
qt6_dep = dependency('qt6', modules: ['Core', 'Gui', 'Widgets'])

moc_files = qt6.compile_moc(
  headers: 'main_qt.h',
  dependencies: qt6_dep,
)

executable('starter_qt',
           sources: ['main_qt.cpp', moc_files],
           dependencies: qt6_dep)
