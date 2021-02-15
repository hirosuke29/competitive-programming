import os
import json


def get_all_file(file_list, current_dir):
    current_dirList = os.listdir(current_dir)
    for content in current_dirList:
        if content[0] == '.' or content == os.path.basename(__file__):
            continue
        target = os.path.join(current_dir, content)
        if os.path.isfile(target):
            file_list.append(target)
        elif os.path.isdir(target):
            file_list.extend(get_all_file(file_list=[], current_dir=target))
    return file_list


def convert_to_snippet(file):
    with open(file) as target:
        line_list = target.readlines()
    fileStr = ''.join(line_list)
    return fileStr


def generate_snippet_dict(file):
    file_name = os.path.splitext(os.path.basename(file))[0]
    snippets = dict()
    snippets[file_name] = dict()
    snippets[file_name]['prefix'] = file_name
    snippets[file_name]['body'] = convert_to_snippet(file)
    return snippets


def add_snippet(current_dir, json_file, indent):
    file_list = get_all_file(file_list=[], current_dir=current_dir)
    file_dict = dict()
    for file in file_list:
        file_dict.update(generate_snippet_dict(file))
    with open(json_file, 'w') as snippets_json:
        json.dump(file_dict, snippets_json, indent=indent)
    return


if __name__ == '__main__':
    with open('setting.json', 'r') as setting_file:
        setting = json.load(setting_file)
        path = setting['path']
        json_path = setting['json_path']
        indent = setting['indent']
        add_snippet(path, json_path, indent)
