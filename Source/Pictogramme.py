class Pictogramme:
	def __init__(self, classe, rank):
		self.classe = classe
		self.values = []
		self.rank = rank

	def add_value(self, extracted_values):
		self.values.append(extracted_values[self.rank])