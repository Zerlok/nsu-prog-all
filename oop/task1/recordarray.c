#include <stdio.h>
#include <stdlib.h>
#include <string.h>	

#include "recordarray.h"


RecordArray *ra_create(size_t size, size_t record_size)
{
	if (((int)size < 0)
			|| ((int)record_size <= 0))
		return NULL;

	RecordArray *self = (RecordArray*)malloc(sizeof(RecordArray));
	self->m_size = size;
	self->m_record_size = record_size;
	self->m_data = (void*)calloc(self->m_size, self->m_record_size);
	self->f_element_printor = NULL;

	return self;
}


int ra_is_valid_index(RecordArray *self, size_t idx)
{
	return (((int)idx >= 0)
		&& (idx < self->m_size));
}


void *ra_get(RecordArray *self, size_t idx)
{
	if ((self == NULL)
			|| !ra_is_valid_index(self, idx))
		return NULL;

	return self->m_data + (idx * (self->m_record_size));
}


void ra_set(RecordArray *self, size_t idx, void *record)
{
	void *data = ra_get(self, idx);
	if (data == NULL)
		return;

	memcpy(data, record, self->m_record_size);
}


void ra_print(RecordArray *self)
{
	if ((self == NULL)
			|| (self->f_element_printor == NULL))
		return;

	printf("[");

	size_t i;
	void *element;
	for (i = 0; i < self->m_size; i++)
	{
		element = ra_get(self, i);
		self->f_element_printor(element);
	}

	printf("]\n");
}


void ra_delete(RecordArray *self)
{
	if (self == NULL)
		return;

	free(self->m_data);
	free(self);
}
