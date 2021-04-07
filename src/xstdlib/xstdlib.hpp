#ifndef ENGINE_XSTDLIB_H
#define ENGINE_XSTDLIB_H

template <class T>
struct linked_list {
	T *data;
	struct linked_list *next;

	linked_list(T *a_data, struct linked_list *a_next)
		: data(a_data), next(a_next) { }
};

char *xfread(const char *path, const char *mode);

#endif /* ENGINE_XSTDLIB_H */
