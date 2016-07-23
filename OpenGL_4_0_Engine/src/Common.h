#ifndef _COMMON_H_
#define _COMMON_H_

#define glVerifyState() { \
unsigned int error = glGetError(); \
std::string out; \
while (error) {\
	switch (error) { \
	case GL_INVALID_OPERATION: \
		out = "INVALID_OPERATION"; \
		break; \
	case GL_INVALID_ENUM: \
		out = "INVALID_ENUM"; \
		break; \
	case GL_INVALID_VALUE: \
		out = "INVALID_VALUE"; \
		break; \
	case GL_OUT_OF_MEMORY: \
		out = "OUT_OF_MEMORY"; \
		break; \
	case GL_INVALID_FRAMEBUFFER_OPERATION: \
		out = "INVALID_FRAMEBUFFER_OPERATION"; \
		break; \
	default: \
		out = "UNKNOWN"; \
		break; \
	} \
	printf("%s: at %s, line %d\n", \
	out.c_str(), __FILE__, __LINE__); \
	error = glGetError(); \
}}

#endif
