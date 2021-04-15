'''
This script extract a few specific definitions from app-ethereum that are
required to exchange information with ethereum external plugins.
It should always be launched from app-ethereum:

python3 ethereum-plugin-sdk/build_sdk.py

'''

import os

def extract_from_headers(sources, nodes_to_extract):
    cat_sources = []
    for source in sources:
        with open(source, 'r') as f:
            cat_sources += f.readlines()

    sdk_body = []
    for key, values in nodes_to_extract.items():
        for value in values:
            node = []
            unclosed_curvy_brackets = 0
            for line in cat_sources:
                if key in line and value in line:
                    node += [line]
                    unclosed_curvy_brackets = line.count('{') - line.count('}')
                    if unclosed_curvy_brackets == 0:
                        break
                elif unclosed_curvy_brackets:
                    node += [line]
                    unclosed_curvy_brackets += line.count('{') - line.count('}')
                    if unclosed_curvy_brackets:
                        continue
                    else:
                        break

            sdk_body += [''.join(node)]


    return '\n'.join(sdk_body)

def merge_headers(sources, nodes_to_extract):
    includes = [
        '#include "os.h"',
        '#include "cx.h"'
    ]

    body = extract_from_headers(sources, nodes_to_extract)

    eth_internals_h = '\n\n'.join([
        "/* This file is auto-generated, don't edit it */",
        "#pragma once",
        '\n'.join(includes),
        body
    ])

    with open("ethereum-plugin-sdk/include/eth_internals.h", 'w') as f:
        f.write(eth_internals_h)


def strip_headers_and_copy(merged_headers, headers_to_strip_and_copy):

    merged_headers = [os.path.basename(path) for path in merged_headers]

    with open("src/eth_plugin_interface.h", 'r') as f:
        source = f.readlines()

    eth_plugin_interface_h = ["/* This file is auto-generated, don't edit it */\n"]
    for line in source:
        eth_plugin_interface_h += [line]
        for header in merged_headers:
            if header in line:
                del eth_plugin_interface_h[-1]
                break

    # add '#include "eth_internals.h"'
    include_index = eth_plugin_interface_h.index('#include "cx.h"\n')
    eth_plugin_interface_h.insert(include_index+1, '#include "eth_internals.h"\n')

    # dump to file
    with open("ethereum-plugin-sdk/include/eth_plugin_interface.h", 'w') as f:
        f.writelines(eth_plugin_interface_h)



if __name__ == "__main__":

    # some nodes will be extracted from these headers and merged into a new one
    headers_to_merge = [
        "src/tokens.h",
        "src_common/ethUstream.h",
    ]
    nodes_to_extract = {
        "#define": ["MAX_TICKER_LEN"],
        "typedef struct": ["tokenDefinition_t", "txInt256_t", "txContent_t"]
    }
    merge_headers(headers_to_merge, nodes_to_extract)

    # these headers will be stripped from all #include related to previously merged headers
    headers_to_strip_and_copy = [
        "src/eth_plugin_interface.h"
    ]
    strip_headers_and_copy(headers_to_merge, headers_to_strip_and_copy)

