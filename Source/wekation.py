# -*- coding: utf-8 -*-
import re
import array

def toWeka(file_path, result_filename):
	
	# open file
	print('opening file')
	f = open(file_path, 'r')

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
					res.write(value + ',' + picto_class + '\n')
				res.write('\n')

				# read next line
				line = f.readline().rstrip()

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
	print('---------------main----------------')
	print('--------------example----------------')
	fichierTest = 'C:/Users/Bamako/Documents/Visual Studio 2012/Projects/caract/caract/resultat/contourArea.txt'
	fichierRes = 'contourArea.arff'
	toWeka(fichierTest, fichierRes)

main()