/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "Specs", "index.html", [
    [ "What?", "index.html#autotoc_md1", null ],
    [ "Why?", "index.html#autotoc_md2", null ],
    [ "✨ Quick Start", "md__documentation_2_quick_start.html", [
      [ "Project Templates", "md__documentation_2_quick_start.html#autotoc_md4", [
        [ "xmake template", "md__documentation_2_quick_start.html#autotoc_md5", null ],
        [ "CMake/vcpkg template", "md__documentation_2_quick_start.html#autotoc_md6", null ]
      ] ]
    ] ],
    [ "⬇️ Installing Specs", "md__documentation_2_installing.html", [
      [ "C++17", "md__documentation_2_installing.html#autotoc_md8", null ],
      [ "xmake", "md__documentation_2_installing.html#autotoc_md9", [
        [ "Verify", "md__documentation_2_installing.html#autotoc_md10", null ],
        [ "Assertion Library Support", "md__documentation_2_installing.html#autotoc_md11", null ],
        [ "Snowhouse", "md__documentation_2_installing.html#autotoc_md12", [
          [ "Verify", "md__documentation_2_installing.html#autotoc_md13", null ]
        ] ],
        [ "libassert", "md__documentation_2_installing.html#autotoc_md14", [
          [ "Verify", "md__documentation_2_installing.html#autotoc_md15", null ]
        ] ]
      ] ],
      [ "vcpkg", "md__documentation_2_installing.html#autotoc_md16", [
        [ "vcpkg-configuration.json", "md__documentation_2_installing.html#autotoc_md18", null ],
        [ "CMakeLists.txt", "md__documentation_2_installing.html#autotoc_md19", null ],
        [ "Verify", "md__documentation_2_installing.html#autotoc_md20", null ],
        [ "Assertion Library Support", "md__documentation_2_installing.html#autotoc_md21", [
          [ "vcpkg.json", "md__documentation_2_installing.html#autotoc_md17", null ],
          [ "Snowhouse", "md__documentation_2_installing.html#autotoc_md22", [
            [ "vcpkg.json", "md__documentation_2_installing.html#autotoc_md23", null ],
            [ "CMakeLists.txt", "md__documentation_2_installing.html#autotoc_md24", null ],
            [ "Verify", "md__documentation_2_installing.html#autotoc_md25", null ]
          ] ],
          [ "libassert", "md__documentation_2_installing.html#autotoc_md26", null ]
        ] ]
      ] ]
    ] ],
    [ "✏️ Writing Tests", "md__documentation_2_writing_tests.html", [
      [ "Creating a project", "md__documentation_2_writing_tests.html#autotoc_md28", [
        [ "Entrypoint", "md__documentation_2_writing_tests.html#autotoc_md29", null ]
      ] ],
      [ "Creating test files", "md__documentation_2_writing_tests.html#autotoc_md30", [
        [ "Test file #define header", "md__documentation_2_writing_tests.html#autotoc_md31", [
          [ "#define SPEC_CONTEXT", "md__documentation_2_writing_tests.html#autotoc_md32", null ],
          [ "#define SPEC_FILE", "md__documentation_2_writing_tests.html#autotoc_md33", null ],
          [ "#define SPEC_GROUP", "md__documentation_2_writing_tests.html#autotoc_md34", null ],
          [ "#define SPEC_TEMPLATE", "md__documentation_2_writing_tests.html#autotoc_md35", null ]
        ] ]
      ] ],
      [ "Tests", "md__documentation_2_writing_tests.html#autotoc_md36", [
        [ "Skipping Tests", "md__documentation_2_writing_tests.html#autotoc_md37", null ],
        [ "Accessing Test Information", "md__documentation_2_writing_tests.html#autotoc_md38", null ]
      ] ],
      [ "Async Tests", "md__documentation_2_writing_tests.html#autotoc_md39", [
        [ "Async timeout", "md__documentation_2_writing_tests.html#autotoc_md40", null ]
      ] ],
      [ "Test assertions", "md__documentation_2_writing_tests.html#autotoc_md41", [
        [ "Snowhouse assertions", "md__documentation_2_writing_tests.html#autotoc_md42", null ],
        [ "libassert assertions", "md__documentation_2_writing_tests.html#autotoc_md43", null ]
      ] ],
      [ "Setup and Teardown", "md__documentation_2_writing_tests.html#autotoc_md44", [
        [ "Asynchronous Setup and Teardown", "md__documentation_2_writing_tests.html#autotoc_md45", null ],
        [ "Accessing Setup/Teardown Information", "md__documentation_2_writing_tests.html#autotoc_md46", null ]
      ] ],
      [ "Test Groups", "md__documentation_2_writing_tests.html#autotoc_md47", [
        [ "Unique test group for each file", "md__documentation_2_writing_tests.html#autotoc_md48", null ]
      ] ],
      [ "Nesting child groups", "md__documentation_2_writing_tests.html#autotoc_md49", null ]
    ] ],
    [ "🏃‍♀️ Running Tests", "md__documentation_2_running_tests.html", [
      [ "Specs executable project", "md__documentation_2_running_tests.html#autotoc_md57", [
        [ "<Specs/Main.h>", "md__documentation_2_running_tests.html#autotoc_md58", null ]
      ] ],
      [ "Run executable project", "md__documentation_2_running_tests.html#autotoc_md59", [
        [ "Running tests", "md__documentation_2_running_tests.html#autotoc_md60", null ],
        [ "Help documentation", "md__documentation_2_running_tests.html#autotoc_md61", null ]
      ] ],
      [ "Command-Line Options", "md__documentation_2_running_tests.html#autotoc_md62", null ],
      [ "Test runners", "md__documentation_2_running_tests.html#autotoc_md63", null ],
      [ "Test reporters", "md__documentation_2_running_tests.html#autotoc_md64", null ]
    ] ],
    [ "▶️ Command-Line Interface", "md__documentation_2_c_l_i.html", null ],
    [ "📂 Project Layout", "md__documentation_2_project_layout.html", null ],
    [ "✔️ Assertion Libraries", "md__documentation_2_assertion_libraries.html", [
      [ "Assertion Libraries", "md__documentation_2_assertion_libraries.html#autotoc_md68", [
        [ "snowhouse", "md__documentation_2_assertion_libraries.html#autotoc_md69", [
          [ "Setup", "md__documentation_2_assertion_libraries.html#autotoc_md70", null ],
          [ "Usage", "md__documentation_2_assertion_libraries.html#autotoc_md71", null ]
        ] ],
        [ "libassert", "md__documentation_2_assertion_libraries.html#autotoc_md72", null ]
      ] ]
    ] ],
    [ "📋 Shared Code Templates", "md__documentation_2_templates.html", [
      [ "What is a template?", "md__documentation_2_templates.html#autotoc_md74", null ],
      [ "Defining Templates", "md__documentation_2_templates.html#autotoc_md75", [
        [ "#define SPEC_TEMPLATE Template_Name", "md__documentation_2_templates.html#autotoc_md76", null ],
        [ "TestTemplate() / EndTestTemplate()", "md__documentation_2_templates.html#autotoc_md77", null ],
        [ "StartTestTemplate() / EndTestTemplate()", "md__documentation_2_templates.html#autotoc_md78", null ],
        [ "Load your templates before your tests!", "md__documentation_2_templates.html#autotoc_md79", null ]
      ] ],
      [ "Using Templates", "md__documentation_2_templates.html#autotoc_md80", [
        [ "Lambda syntax", "md__documentation_2_templates.html#autotoc_md81", null ]
      ] ]
    ] ],
    [ "💲 Test Variables", "md__documentation_2_variables.html", [
      [ "Using Variables", "md__documentation_2_variables.html#autotoc_md83", [
        [ "Setting Variables", "md__documentation_2_variables.html#autotoc_md84", [
          [ "Simple Values", "md__documentation_2_variables.html#autotoc_md85", null ],
          [ "Text", "md__documentation_2_variables.html#autotoc_md86", null ],
          [ "Complex Types", "md__documentation_2_variables.html#autotoc_md87", null ]
        ] ],
        [ "Getting Variables", "md__documentation_2_variables.html#autotoc_md88", [
          [ "Text", "md__documentation_2_variables.html#autotoc_md89", null ]
        ] ],
        [ "Unsetting Values", "md__documentation_2_variables.html#autotoc_md90", null ],
        [ "Variable Lifetime", "md__documentation_2_variables.html#autotoc_md91", [
          [ "Variable lifetime helpers", "md__documentation_2_variables.html#autotoc_md92", [
            [ "managed_var", "md__documentation_2_variables.html#autotoc_md93", null ],
            [ "unmanaged_var", "md__documentation_2_variables.html#autotoc_md94", null ]
          ] ],
          [ "Editing the lifetime of a variable", "md__documentation_2_variables.html#autotoc_md95", null ]
        ] ]
      ] ]
    ] ],
    [ "🎟️ Test Tags", "md__documentation_2_tags.html", null ],
    [ "🛢️ Test Data", "md__documentation_2_data.html", null ],
    [ "🔍 Test Info", "md__documentation_2_test_info.html", null ],
    [ "💥 Exception Handling", "md__documentation_2_exceptions.html", null ],
    [ "🏎️ Test Runners", "md__documentation_2_runners.html", null ],
    [ "🗣️ Test Reporters", "md__documentation_2_reporters.html", null ],
    [ "💾 Shared Libraries", "md__documentation_2_shared_libraries.html", null ],
    [ "📖 Syntax Reference", "md__documentation_2_syntax_reference.html", null ],
    [ "🖋️ Customizing Syntax", "md__documentation_2_custom_syntax.html", null ],
    [ "🪄 Available Macros", "md__documentation_2_macros.html", null ],
    [ "👥 Data Model", "md__documentation_2_data_model.html", null ],
    [ "🧐 Examples", "md__documentation_2_examples.html", null ],
    [ "🤝 CONTRIBUTING", "md__documentation_2_c_o_n_t_r_i_b_u_t_i_n_g.html", null ],
    [ "💖 LICENSE (0BSD)", "md__documentation_2_l_i_c_e_n_s_e.html", null ],
    [ "🐙 GitHub Repository", "md__documentation_2_git_hub.html", null ],
    [ "Namespaces", "namespaces.html", [
      [ "Namespace List", "namespaces.html", "namespaces_dup" ],
      [ "Namespace Members", "namespacemembers.html", [
        [ "All", "namespacemembers.html", null ],
        [ "Functions", "namespacemembers_func.html", null ],
        [ "Variables", "namespacemembers_vars.html", null ],
        [ "Typedefs", "namespacemembers_type.html", null ],
        [ "Enumerations", "namespacemembers_enum.html", null ]
      ] ]
    ] ],
    [ "Classes", "annotated.html", [
      [ "Class List", "annotated.html", "annotated_dup" ],
      [ "Class Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", "functions_func" ],
        [ "Typedefs", "functions_type.html", null ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "File Members", "globals.html", [
        [ "All", "globals.html", null ],
        [ "Functions", "globals_func.html", null ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Macros", "globals_defs.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"_a_p_i_2_internal_2_documented_2_a_p_i_8h.html",
"_o_n_e___t_i_m_e___s_e_t_u_p_8h.html#a0e9924da9fa4ef3e1f0312f0e566c184",
"_top_level_2test_8h.html#aa73c0e1a19248bc75f44b13b45e890ee",
"class_specs_cpp_1_1_spec_console_output.html#a17e4438559e50ac61185987d92e2142f",
"class_specs_cpp_1_1_spec_run_result.html#a1164ab6772b95f2cb868c2dceac5aaab",
"md__documentation_2_installing.html#autotoc_md8",
"struct_specs_cpp_1_1_i_local_spec_exception_handler_collection.html#a02523a3ade93df58978e939123d7265a",
"struct_specs_cpp_1_1_i_spec_group.html#ac3c88771cbfaeed06fc2daa94b5ed46d",
"struct_specs_cpp_1_1_interfaces_1_1_i_spec_application.html"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';