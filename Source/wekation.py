# -*- coding: utf-8 -*-
import re
import array
import os

def weka_process_folder(folder_path):
	for dirname, dirnames, filenames in os.walk(folder_path):
	    for filename in filenames:
	    	if os.path.splitext(filename)[1] == '.txt':
		        filepath = os.path.join(dirname, filename)
		        print('-------------------------------------')
		        print('Processing ' + filepath)
		        output_filename = os.path.splitext(filename)[0] + '.arff'
		        toWeka(filepath, output_filename)

def toWeka(filepath, result_filename):
	# open file
	print('opening file')
	f = open(filepath, 'r')

	try:
		caract = f.readline().rstrip()
		# open result file
		print('opening result file')
		res = open(result_filename, 'w+')
		try:
			# write result
			res.write('@RELATION test\n')
			res.write('@ATTRIBUTE ' + caract + ' NUMERIC\n')
			res.write('\n')
			res.write('@DATA')
			res.write('\n')
			print('initialization complete')
		
			line = f.readline().rstrip()

			while line != '':
				# process line for results
				# find attribute name
				picto_class = re.findall('(.+?)\s=', line)
				picto_class = picto_class[0]
				
				# find attribute values
				values = re.findall('\[\s(.+?)\s\]', line)
				values = values[0].replace(" ", "").split(';')

				# write results
				print('writing data for ' + picto_class)
				for value in values:
					try:
						value = float(value)
						res.write(str(value) + ',' + picto_class + '\n')
					except ValueError:
						print('"-1.#IND" detected. Skipping...')

				# read next line
				line = f.readline().rstrip()
				res.write('\n')

			print('writing complete')
		
		finally:
			# close result file
			print('closing result file')
			res.close()

	finally:
		# close file
		print('closing file')
		f.close

	print('reading done')

def main():
	print('----------------main-----------------')

	print('--------------example----------------')
	weka_process_folder("C:/Users/Bamako/Documents/Visual Studio 2012/Projects/caract/caract/resultat/")

main()