#ifndef SHADER_HPP
#define SHADER_HPP

GLuint CompileShaders(const char * vertex_code, const char * fragment_code);
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif
