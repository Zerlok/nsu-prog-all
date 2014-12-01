template <class Pointer>
class AutoPointer
{
	public:
		AutoPointer();
		~AutoPointer();
		
		AutoPointer(Pointer *p);
		
		AutoPointer(AutoPointer& auto_ptr)

		Pointer *release();
		Pointer *reset(Pointer *p);

		AutoPointer& operator=(AutoPointer& auto_ptr);
		Pointer& operator*() const;
		Pointer *operator->() const;

	private:
		Pointer *_ptr;
};
