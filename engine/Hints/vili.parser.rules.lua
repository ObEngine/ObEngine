---@meta

vili.parser.rules = {};
---@class vili.parser.rules.affectation : peg.seq[vili.parser.rules.identifier,peg.pad[peg.must[vili.parser.rules.affectation_separator>,peg.blank]]]
vili.parser.rules._affectation = {};



---@class vili.parser.rules.affectation_separator : peg.one[':']
vili.parser.rules._affectation_separator = {};



---@class vili.parser.rules.array : tao.pegtl.seq[vili.parser.rules.open_array,peg.pad_opt[vili.parser.rules.array_elements,vili.parser.rules.space_or_comment>,peg.must[vili.parser.rules.close_array]]]
vili.parser.rules._array = {};



---@class vili.parser.rules.array_elements : peg.list_must[vili.parser.rules.inline_element,vili.parser.rules.array_separator,vili.parser.rules.space_or_comment]
vili.parser.rules._array_elements = {};



---@class vili.parser.rules.array_separator : tao.pegtl.one[',']
vili.parser.rules._array_separator = {};



---@class vili.parser.rules.block : peg.sor[vili.parser.rules.empty_line,vili.parser.rules.inline_comment,vili.parser.rules.multiline_comment_block,vili.parser.rules.full_node]
vili.parser.rules._block = {};



---@class vili.parser.rules.boolean : tao.pegtl.sor[vili.parser.rules.true_,vili.parser.rules.false_]
vili.parser.rules._boolean = {};



---@class vili.parser.rules.brace_based_object : tao.pegtl.seq[vili.parser.rules.open_object,peg.pad_opt[vili.parser.rules.object_elements,vili.parser.rules.space_or_comment>,peg.must[vili.parser.rules.close_object]]]
vili.parser.rules._brace_based_object = {};



---@class vili.parser.rules.char_ : peg.if_then_else[peg.one['\'>,peg.must[vili.parser.rules.escaped>,vili.parser.rules.unescaped]]]
vili.parser.rules._char_ = {};



---@class vili.parser.rules.close_array : tao.pegtl.one[']']
vili.parser.rules._close_array = {};



---@class vili.parser.rules.close_object : tao.pegtl.one['}']
vili.parser.rules._close_object = {};



---@class vili.parser.rules.comment : tao.pegtl.sor[vili.parser.rules.inline_comment,vili.parser.rules.multiline_comment]
vili.parser.rules._comment = {};



---@class vili.parser.rules.data : tao.pegtl.sor[vili.parser.rules.boolean,vili.parser.rules.number,vili.parser.rules.integer,vili.parser.rules.string]
vili.parser.rules._data = {};



---@class vili.parser.rules.digits : peg.plus[peg.digit]
vili.parser.rules._digits = {};



---@class vili.parser.rules.element : tao.pegtl.sor[vili.parser.rules.data,vili.parser.rules.array,vili.parser.rules.object]
vili.parser.rules._element = {};



---@class vili.parser.rules.empty_line : tao.pegtl.seq[peg.star[peg.blank>,peg.eol]]
vili.parser.rules._empty_line = {};



---@class vili.parser.rules.endline : tao.pegtl.sor[vili.parser.rules.inline_comment,peg.eol]
vili.parser.rules._endline = {};



---@class vili.parser.rules.escaped : tao.pegtl.sor[vili.parser.rules.escaped_char,vili.parser.rules.unicode]
vili.parser.rules._escaped = {};



---@class vili.parser.rules.escaped_char : peg.one['"','\','/','b','f','n','r','t']
vili.parser.rules._escaped_char = {};



---@class vili.parser.rules.false_ : peg.string['f','a','l','s','e']
vili.parser.rules._false_ = {};



---@class vili.parser.rules.floating_point : tao.pegtl.one['.']
vili.parser.rules._floating_point = {};



---@class vili.parser.rules.full_node : tao.pegtl.seq[vili.parser.rules.indent,peg.star[vili.parser.rules.multiline_comment>,vili.parser.rules.node,peg.star[vili.parser.rules.multiline_comment_block>,peg.opt[vili.parser.rules.endline]]]]
vili.parser.rules._full_node = {};



---@class vili.parser.rules.grammar : peg.must[vili.parser.rules.vili_grammar]
vili.parser.rules._grammar = {};



---@class vili.parser.rules.identifier : peg.identifier
vili.parser.rules._identifier = {};



---@class vili.parser.rules.indent : tao.pegtl.seq[peg.bol,peg.star[peg.blank]]
vili.parser.rules._indent = {};



---@class vili.parser.rules.indent_based_object : tao.pegtl.sor[vili.parser.rules.endline,peg.seq[vili.parser.rules.multiline_comment,peg.eol]]
vili.parser.rules._indent_based_object = {};



---@class vili.parser.rules.inline_comment : tao.pegtl.seq[peg.star[peg.blank>,peg.one['#'>,peg.until[peg.eolf]]]]
vili.parser.rules._inline_comment = {};



---@class vili.parser.rules.inline_element : tao.pegtl.sor[vili.parser.rules.boolean,vili.parser.rules.number,vili.parser.rules.integer,vili.parser.rules.string,vili.parser.rules.array,vili.parser.rules.brace_based_object]
vili.parser.rules._inline_element = {};



---@class vili.parser.rules.inline_node : tao.pegtl.seq[vili.parser.rules.affectation,vili.parser.rules.inline_element]
vili.parser.rules._inline_node = {};



---@class vili.parser.rules.integer : tao.pegtl.seq[peg.opt[vili.parser.rules.sign>,vili.parser.rules.digits]]
vili.parser.rules._integer = {};



---@class vili.parser.rules.multiline_comment : tao.pegtl.seq[peg.string['/',' *'>,peg.until[peg.string[' *','/'>,peg.sor[vili.parser.rules.multiline_comment,peg.any]]]]]
vili.parser.rules._multiline_comment = {};



---@class vili.parser.rules.multiline_comment_block : tao.pegtl.seq[peg.plus[peg.pad[vili.parser.rules.multiline_comment,peg.blank>>,peg.sor[vili.parser.rules.endline,peg.eolf]]]]
vili.parser.rules._multiline_comment_block = {};



---@class vili.parser.rules.node : tao.pegtl.seq[vili.parser.rules.affectation,peg.must[vili.parser.rules.element]]
vili.parser.rules._node = {};



---@class vili.parser.rules.number : tao.pegtl.seq[peg.opt[vili.parser.rules.sign>,peg.star[peg.digit>,peg.one['.'>,vili.parser.rules.digits]]]]
vili.parser.rules._number = {};



---@class vili.parser.rules.object : tao.pegtl.sor[vili.parser.rules.brace_based_object,vili.parser.rules.indent_based_object]
vili.parser.rules._object = {};



---@class vili.parser.rules.object_elements : tao.pegtl.list_must[vili.parser.rules.inline_node,vili.parser.rules.object_separator,vili.parser.rules.space_or_comment]
vili.parser.rules._object_elements = {};



---@class vili.parser.rules.object_separator : tao.pegtl.one[',']
vili.parser.rules._object_separator = {};



---@class vili.parser.rules.open_array : tao.pegtl.one['[']
vili.parser.rules._open_array = {};



---@class vili.parser.rules.open_object : tao.pegtl.one['{']
vili.parser.rules._open_object = {};



---@class vili.parser.rules.sign : tao.pegtl.one['-']
vili.parser.rules._sign = {};



---@class vili.parser.rules.space_or_comment : tao.pegtl.sor[vili.parser.rules.comment,peg.space]
vili.parser.rules._space_or_comment = {};



---@class vili.parser.rules.string : tao.pegtl.seq[vili.parser.rules.string_delimiter,peg.must[vili.parser.rules.string_content>,peg.any]]
vili.parser.rules._string = {};



---@class vili.parser.rules.string_content : peg.until[peg.at[vili.parser.rules.string_delimiter>,peg.must[vili.parser.rules.char_]]]
vili.parser.rules._string_content = {};



---@class vili.parser.rules.string_delimiter : tao.pegtl.one['"']
vili.parser.rules._string_delimiter = {};



---@class vili.parser.rules.true_ : tao.pegtl.string['t','r','u','e']
vili.parser.rules._true_ = {};



---@class vili.parser.rules.unescaped : peg.utf8.range[0x20,0x10FFFF]
vili.parser.rules._unescaped = {};



---@class vili.parser.rules.unicode : peg.list[peg.seq[peg.one['u'>,peg.rep[4,peg.must[vili.parser.rules.xdigit>>>,peg.one['\']]]]]]
vili.parser.rules._unicode = {};



---@class vili.parser.rules.vili_grammar : tao.pegtl.until[peg.eof,peg.must[vili.parser.rules.block]]
vili.parser.rules._vili_grammar = {};



---@class vili.parser.rules.xdigit : peg.xdigit
vili.parser.rules._xdigit = {};



return vili.parser.rules;