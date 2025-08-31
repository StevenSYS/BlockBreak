#ifndef __MISC__
#define __MISC__
	#define LESSTHANSET(_var, _value) \
		if (_var < _value) { \
			_var = _value; \
		}
	
	#define SAFEADD(_var, _value, _max) \
		if ((_var + _value) > _max) { \
			_var = _max; \
		} else { \
			_var += _value; \
		}
#endif