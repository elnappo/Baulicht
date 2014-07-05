try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup


setup(
    name='Baulicht',
    version='0.2.1',
    description='dbus wrapper for Baulicht project',
    install_requires=['dbus-python'],
    py_modules=['pybaulicht'],
    url='https://github.com/elnappo/Baulicht/tree/master/pybaulicht',
    license='MIT',
    author='elnappo',
    author_email='elnappoo@gmail.com'
)
