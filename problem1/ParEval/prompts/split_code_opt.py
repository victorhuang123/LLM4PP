from abc import ABC, abstractmethod
from argparse import ArgumentParser
import json
import os
import re
from typing import List


def main():
    datas = []
    with open("./code_opt.json", "r") as fr:
        datas = json.load(fr)
    print(len(datas))

    tgts = {
        "09_fft_fft_out_of_place",
        "27_reduce_average",
        "47_sparse_la_spmv",
        "14_geometry_closest_pair_1d",
        "31_scan_scan_with_min_function",
        "22_histogram_count_quadrants",
        "36_search_check_if_array_contains_value",
        "41_sort_k-th_smallest_element",
        "50_stencil_xor_kernel",
        "55_transform_relu",
        "19_graph_shortest_path",
        "01_dense_la_solve",
    }
    datas_48 = []
    datas_24 = []
    for data in datas:
        number = data["name"].split("_")[0]
        if data["name"] in tgts or int(number) >= 60:
            datas_24.append(data)
        else:
            datas_48.append(data)

    print(len(datas_48))
    print(len(datas_24))
    # sorted by key
    datas_48.sort(key=lambda x: x["name"])
    datas_24.sort(key=lambda x: x["name"])

    with open("./code_opt_48.json", "w") as fw:
        json.dump(datas_48, fw, indent=4)
    with open("./code_opt_24.json", "w") as fw:
        json.dump(datas_24, fw, indent=4)


if __name__ == "__main__":
    main()