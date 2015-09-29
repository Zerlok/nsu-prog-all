#ifndef __RECORDARRAY_H__
#define __RECORDARRAY_H__


typedef struct _RecordArray {
	size_t m_size;
	size_t m_record_size;
	void *m_data;

	void (*f_element_printor)(void *ptr);
} RecordArray;


// Создать новый массив начального размера size, размер элемента record_size
RecordArray *ra_create(size_t size, size_t record_size);

// Получить указатель на запись из массива
void *ra_get(RecordArray *self, size_t idx);

// Заменить запись в массиве, скопировав данные из record
void ra_set(RecordArray *self, size_t idx, void *record);

// Print the array.
void ra_print(RecordArray *self);

// Уничтожить массив
void ra_delete(RecordArray *self);


// __RECORDARRAY_H__
#endif
