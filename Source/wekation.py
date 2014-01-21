# -*- coding: utf-8 -*-
import re
import array
import os
from Pictogramme import Pictogramme

# data structures
classes = ['allonge', 'attention', 'bombe', 'croix', 'flamme', 'fleche', 'homme', 'interdit', 'parking', 'tetemort', 'trianglef', 'vague', 'voiture', 'zzz']
analysed_caracteristics = []
dict_values = {}

def initiate_classes():
	print('--------------initiate_classes----------------')
	if (dict_values == {}):
		for c in classes:
			imagettes = []
			dict_values[c] = imagettes

def weka_process_folder(folder_path):
	for dirname, dirnames, filenames in os.walk(folder_path):
		for filename in filenames:
			if os.path.splitext(filename)[1] == '.txt':
				filepath = os.path.join(dirname, filename)
				print('-------------------------------------')
				print('Processing ' + filepath)
				output_filename = os.path.splitext(filename)[0] + '.arff'
				analysed_caracteristics.append(os.path.splitext(filename)[0])
				toWeka(filepath)
		write_arff("output.arff")

def toWeka(filepath):
	print('--------------toWeka----------------')
	# open file
	print('opening file')
	f = open(filepath, 'r')

	try:
		caract = f.readline().rstrip()
		line = f.readline().rstrip()

		while line != '':
			# process line for results
			# find attribute name
			picto_class = re.findall('(.+?)\s=', line)
			picto_class = picto_class[0]
			
			# find attribute values
			extracted_values = re.findall('\[\s(.+?)\s\]', line)
			extracted_values = extracted_values[0].replace(" ", "").split(';')

			for x in range(0, len(extracted_values)):

				if (len(dict_values[picto_class]) <= x):
					print('no pictos')
					print('adding the analysed image')
					p = Pictogramme(picto_class, x)
					p.values.append(extracted_values[x])
					dict_values[picto_class].append(p)

				elif (x < len(extracted_values)):
					print('get picto & add value')
					dict_values[picto_class][x].values.append(extracted_values[x])
					print('added value ', extracted_values[x])

				else :
					print('problem')

			line = f.readline().rstrip()

	finally:
		# close file
		print('closing file')
		f.close

	print('reading done')

def write_arff(result_filename):
	# open result file
	print('opening result file')
	res = open(result_filename, 'w+')

	try:
		# write result
		res.write('@RELATION caracteristiques\n')

		for c in analysed_caracteristics:
			res.write('@ATTRIBUTE ')
			res.write(c)
			res.write(' NUMERIC\n')

		res.write('@ATTRIBUTE class {')
		for c in classes:
			res.write(c)
			if (classes.index(c) < len(classes) - 1):
				res.write(', ')
		res.write('}\n')
		
		res.write('\n')
		res.write('@DATA')
		res.write('\n')
		print('initialization complete')

		# write results
		for c in classes:
			for p in dict_values[c]:
				print('writing data for ' + p.classe + ' n' + str(p.rank))
				for value in p.values:
					try:
						value = float(value)
						res.write(str(value) + ',')
					except ValueError:
						print('"-1.#IND" detected. Writing 0.0')
						res.write("0.0" + ',')

				res.write(p.classe + '\n')
	
	finally:
		# close result file
		print('closing result file')
		res.close()

	print('writing done')


def main():
	print('----------------main-----------------')

	print('--------------example----------------')
	initiate_classes()
	weka_process_folder("C:/Users/Bamako/Documents/5INFO/IRF/valeurs")

main()