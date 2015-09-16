#include <stdio.h>
#include <stdlib.h>
#include <string.h>	

#include "recordarray.h"


RecordArray *ra_create(size_t size, size_t record_size)
{
	printf("Creating the array of records...\n");

	if ((size < 0)
			|| (record_size <= 0))
		return NULL;

	// Assigning fields.
	RecordArray *self = (RecordArray*)malloc(sizeof(RecordArray));
	self->m_size = size;
	self->m_record_size = record_size;
	self->m_data = (void*)calloc(self->m_size, self->m_record_size);

	// Assigning methods.
	self->f_element_printor = NULL;

	return self;
}


int ra_is_valid_index(RecordArray *self, int idx)
{
	return ((idx >= 0)
		&& (idx < self->m_size));
}


void *ra_get(RecordArray *self, size_t idx)
{
	// printf("Getting record from array...\n");

	if ((self == NULL)
			|| !ra_is_valid_index(self, idx))
		return;

	return self->m_data + (idx * (self->m_record_size));
}


void ra_set(RecordArray *self, size_t idx, void *record)
{
	// printf("Adding record into array...\n");

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
	for (i = 0; i < self->m_size; i++)
		self->f_element_printor(ra_get(self, i));

	printf("]\n");
}


void ra_delete(RecordArray *self)
{
	if (self == NULL)
		return;

	free(self->m_data);
	free(self);
}
