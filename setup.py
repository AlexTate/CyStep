import setuptools

from setuptools import Extension
from Cython.Build import cythonize

extensions = [
    Extension("test_stepvec",
              sources=['test_stepvec.pyx'],
              extra_compile_args=['-stdlib=libc++', '-std=c++11'],
              language='c++'),
    Extension("_stepvector",
              sources=['_stepvector.pyx'],
              extra_compile_args=['-stdlib=libc++', '-std=c++11'],
              language='c++')
]

setuptools.setup(
    ext_modules = cythonize(extensions, compiler_directives={'language_level': '3'},
                            gdb_debug=True),
    include_dirs=['.']
)