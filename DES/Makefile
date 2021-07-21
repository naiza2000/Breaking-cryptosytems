ri:
	g++ random_inputs.cpp -o bin/random_inputs
	bin/random_inputs
rix:
	g++ random_inputs_xor.cpp -o bin/random_inputs_xor
	bin/random_inputs_xor

script:
	rm -f scripts/get_outputs.sh
	g++ script_gen.cpp -o bin/script_gen
	bin/script_gen

outputs:
	rm -f ssh_outputs.log
	touch ssh_outputs.log
	./scripts/get_outputs.sh

freq:
	rm -f ssh_outputs.log text/frq_samples.txt
	touch ssh_outputs.log
	python freq_sample.py
	g++ freq_gen.cpp -o bin/freq_gen
	bin/freq_gen
	./scripts/get_freq_outputs.sh
	python report_freq.py
