#ifndef __ABSTRACTPARSER_H__
#define __ABSTRACTPARSER_H__


template <class Data>
class AbstractParser
{
	public:
		// Constructors / Destructor.
		AbstractParser()
			: _parsed_data(),
			  _is_input_valid(false),
			  _is_input_parsed(false) {}
		virtual ~AbstractParser() {}

		// Getters.
		Data get_parsed_data() const { return _parsed_data; }
		bool is_input_valid() const { return _is_input_valid; }
		bool is_parsed() const { return _is_input_parsed; }

		// Methods.
		/*
		 * Parses input data to output data.
		 * Returns false, if parsing error was occured,
		 * otherwise returns true.
		 */
		virtual bool parse_input() = 0;

		/*
		 * Validates input data to be parsed.
		 * Returns false, if input is invalid,
		 * otherwise returns true.
		 */
		virtual bool validate_input() = 0;

	protected:
		// Fields.
		Data _parsed_data;

		bool _is_input_valid;
		bool _is_input_parsed;
};


namespace parsing_messages
{
	// Errors.
	static const string err_header_validating = "*** Input Validation Error: ";
	static const string err_header_parsing = "*** Input Parsing Error: ";
	static const string err_too_many_parameters = "Too many parameters given at input, ";

	// Warnings.
	static const string war_header = "### Warning ";

	// Messages.
	static const string msg_no_parameters_required = "no parameters required!";
}


// __ABSTRACTPARSER_H__
#endif
