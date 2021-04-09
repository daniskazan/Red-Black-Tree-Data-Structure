import os
from os import listdir
from os.path import isfile, join
import dropbox


class Box:

    def __init__(self, api_key, folder_name):
        self.dbx = dropbox.Dropbox(api_key)
        self.folder = folder_name
        self.create_folder()

    def create_folder(self):
        response = self.dbx.files_list_folder(path='')

        for i in response.entries:
            if type(i) == dropbox.files.FolderMetadata:
                return

        self.dbx.files_create_folder(f'/{self.folder}')

    def __one_file_upload(self, path):
        with open(path, 'rb') as file:
            file = file.read()
            self.dbx.files_upload(file, f'/{self.folder}/{os.path.basename(path)}')

    def upload_files(self, path_to_files):
        if os.path.isfile(path_to_files):
            self.__one_file_upload(path_to_files)
        else:
            files = [f for f in listdir(path_to_files) if isfile(join(path_to_files, f))]
            for i in files:
                self.__one_file_upload(f'{path_to_files}/{i}')

    def clear_folder(self):
        response = self.dbx.files_list_folder(path=f'/{self.folder}')
        for i in response.entries:
            self.dbx.files_delete_v2(f'/{self.folder}/{i.name}')

    def download_default(self):
        try:
            os.mkdir(self.folder)
        except FileExistsError:
            pass
        response = self.dbx.files_list_folder(path=f'/{self.folder}')
        for i in response.entries:
            with open(f'{self.folder}/{i.name}', "wb") as f:
                metadata, res = self.dbx.files_download(path=f'/{self.folder}/{i.name}')
                f.write(res.content)

    # def download_link(self, url):
    #     self.dbx.files_list_folder()
