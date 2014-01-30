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
		write_arff("test.arff")

def toWeka(filepath):
	print('--------------toWeka----------------')
	# open file
	print('opening file')
	f = open(filepath, 'r')

	try:
		picto_class = ''
		c = f.read(1)
		skip = False
		number_classes_analysed = 0

		while c != '':

			# get picto class
			while (c != ' ' and c != '= '):
				picto_class = picto_class + c
				c = f.read(1)

			# read remaining '= [ '
			print('skipping "= [ "')
			print('CHAR', c)
			while c != '[':
				c = f.read(1)
			c = f.read(1)
			print('CHAR', c)

			if c == ' ' and number_classes_analysed >= 13 :
				print(number_classes_analysed)
				print('END SPACE. FINISHED !!!')
				return;

			fin = True
			extracted_values = []

			while (c != ']' and fin):

				# read value
				value = ''
				rank = 0
				
				c = f.read(1)
				while c != ' ':
					value = value + c
					c = f.read(1)

				# read remaining '; '
				c = f.read(1)
				c = f.read(1)
				if value == '-1.#IND':
					extracted_values.insert(rank, float(0.0))
				elif value in classes :
					picto_class = value
					fin = False
				else:
					extracted_values.insert(rank, float(value))
				rank = rank + 1

			print('INCREMENT', number_classes_analysed)
			number_classes_analysed = number_classes_analysed + 1

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
						res.write('0.0,')

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
	weka_process_folder("C:/Users/Bamako/Documents/5INFO/IRF/test/")

main()