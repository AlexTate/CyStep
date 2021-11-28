from setuptools import setup, Extension
from Cython.Build import cythonize

extensions = [
    Extension("CyStep._stepvector",
              sources=['CyStep/_stepvector.pyx'],
              extra_compile_args=['-stdlib=libc++', '-std=c++11'],
              language='c++')
]

setup(
    name='CyStep',
    packages=['CyStep'],
    package_data={'stepvector': ['*.pxd', '*.pyx']},
    ext_modules = cythonize(extensions, compiler_directives={'language_level': '3'},
                            gdb_debug=True),
    zip_safe=False,
)