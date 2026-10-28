import pathlib, subprocess, shutil, json
root=pathlib.Path(__file__).resolve().parents[1]
import tempfile
base=pathlib.Path(tempfile.mkdtemp(prefix='compiler-lab-check-'))
records=[]
def cmd(args,wd):
 p=subprocess.run(args,cwd=wd,text=True,capture_output=True); return {'command':' '.join(args),'exit':p.returncode,'output':p.stdout+p.stderr}
for src in sorted(root.glob('cycle*/*')):
 if src.suffix not in ('.c','.l') or src.stem in ('input','input1','input2','sample'): continue
 if src.suffix=='.l' and src.with_suffix('.y').exists(): kind='yacc'
 elif src.suffix=='.l': kind='lex'
 else: kind='c'
 wd=base/src.stem; wd.mkdir(exist_ok=True)
 logs=[]
 if kind=='yacc': logs.append(cmd(['yacc','-d',str(src.with_suffix('.y'))],wd))
 if kind!='c': logs.append(cmd(['flex',str(src)],wd))
 files=[str(src)] if kind=='c' else (['y.tab.c','lex.yy.c'] if kind=='yacc' else ['lex.yy.c'])
 logs.append(cmd(['gcc','-Wall','-Wextra',*files,'-o','program'],wd))
 for name in ('input.c','input1.c','input2.c'):
  shutil.copy(root/'cycle1'/name,wd/name)
 records.append({'id':src.stem,'source':str(src.relative_to(root)),'build':logs,'runs':[]})
def run(id,label,data='',file=None):
 rec=next(r for r in records if r['id']==id); wd=base/id
 if rec['build'][-1]['exit']: return
 if file: (wd/'input.c').write_text(file)
 try:
  p=subprocess.run(['./program'],cwd=wd,input=data,text=True,capture_output=True,timeout=3)
  result={'label':label,'input':data,'file':file,'exit':p.returncode,'output':p.stdout+p.stderr}
 except subprocess.TimeoutExpired as e: result={'label':label,'input':data,'file':file,'exit':'TIMEOUT','output':str(e.stdout)}
 rec['runs'].append(result)
run('1_1','Supplied input.c',file=(root/'cycle1/input.c').read_text())
run('1_1','Sample file',file='int a = 10; // ignored\na++;\n')
run('1_2','Supplied input1.c')
run('1_3','Supplied input2.c')
run('1_4','Replacement','abc xyz abcabc\n')
run('1_5','Letter counts','Hello World!\n')
for id,good,bad in [('2_1','a+3*(b-2)','a+*b'),('2_2','abc123','1abc'),('2_3','(10+2)*3-8/2','2+*3'),('3_1','a+b*c','a+*b'),('4_2','i+i*i','i+*i'),('4_3','i+i*i','i+*i')]:
 run(id,'Valid sample',good+'\n');run(id,'Invalid sample',bad+'\n')
run('2_2','Leading underscore rejected','_abc\n')
run('2_3','Division by zero','5/0\n')
matrix='3\n- e -\n- - a\n- - -\n'
run('3_2','Epsilon closure',matrix)
run('3_3','Epsilon removal',matrix+'1\n2\n')
run('3_3','Epsilon after symbol','3\n- a -\n- - e\n- - -\n1\n2\n')
run('3_4','Subset construction','2\n2\na b\n2 0 1\n0\n0\n1 1\n1\n1\n')
run('3_5','Equivalent states and unreachable state','4\n2\na b\n1 2\n1 2\n1 2\n3 3\n2\n1 2\n')
run('4_1','Simple grammar','3\nS->AB\nA->a\nB->b\n')
run('4_1','Nullable grammar','4\nS->AB\nA->a\nA->e\nB->b\n')
run('4_1','Nullable suffix FOLLOW','4\nS->AB\nA->a\nB->b\nB->e\n')
run('4_1','Left recursive grammar','2\nE->E+a\nE->a\n')
run('5_1','Constant propagation','4\na=5\nb=a+3\nc=b*2\nd=x+2\n')
run('5_1','Division by zero','1\na=5/0\n')
run('5_2','Intermediate code','a=b+c*d\n')
run('5_2','Equal precedence associativity','a=b-c+d\n')
run('5_2','Repeated operators','a=b+c+d\n')
run('5_3','Assembly output','a=b+c\nd=a-b\ne=b*c\nf=c/b\ng=a\nexit\n')
sample=cmd(['gcc','-Wall','-Wextra',str(root/'cycle3/sample.c'),'-o',str(base/'sample')],base)
sample_run=subprocess.run([str(base/'sample')],capture_output=True,text=True,timeout=3) if sample['exit']==0 else None
(base/'results.json').write_text(json.dumps(records,indent=2))
out=['# Compiler lab: actual compilation and execution results','', 'All 19 lab programs were compiled and executed using GCC, Flex and Yacc after the fixes. Outputs below are captured stdout/stderr; piped input is not echoed, so adjacent prompts may appear on one line. Each input block ends with a newline. These sample runs do not prove correctness for every possible input.','']
for r in records:
 out += ['## '+r['id'].replace('_','.')+' — '+r['source'],'','### Build','']
 for b in r['build']:
  out += ['`'+b['command']+'` — exit '+str(b['exit']),'']
  if b['output']:out+=['```text',b['output'].rstrip(),'```','']
 for t in r['runs']:
  out+=['### '+t['label'],'']
  if t['file'] is not None:out+=['File `input.c`:','```c',t['file'].rstrip(),'```','']
  elif t['input']:out+=['Input:','```text',t['input'].rstrip(),'```','']
  elif r['id'] in ('1_2','1_3'):
   name='input1.c' if r['id']=='1_2' else 'input2.c';out+=['File `'+name+'`:','```text',(root/'cycle1'/name).read_text().rstrip(),'```','']
  out+=['Actual output (exit '+str(t['exit'])+'):','```text',t['output'].rstrip(),'```','']
out+=['## Other C files','','`cycle1/input1.c` and `cycle1/input2.c` are lexer input data, not additional lab programs. `cycle3/sample.c` is a sample C input; it was also compiled separately:','```text',sample['output'].rstrip(),'```','', 'Sample executable exit: '+str(sample_run.returncode if sample_run else 'not built')+'. It produces no output.']
(root/'PROGRAM_RUN_RESULTS.md').write_text('\n'.join(out)+'\n')
failures=[]
for rec in records:
 if rec['build'][-1]['exit'] != 0: failures.append(rec['id']+' build failed')
 for case in rec['runs']:
  if case['exit'] == 'TIMEOUT' or isinstance(case['exit'],int) and case['exit'] < 0:
   failures.append(rec['id']+' crashed: '+case['label'])
 print(rec['id'], 'build:',rec['build'][-1]['exit'], 'runs:',len(rec['runs']))
checks = {
 '2_2': [('Leading underscore rejected','Invalid Identifier')],
 '2_3': [('Valid sample','Result = 32'),('Division by zero','Error: division by zero')],
 '3_1': [('Valid sample','+ a * b c')],
 '3_3': [('Epsilon after symbol',"q0 on 'a' -> q2")],
 '4_1': [('Nullable grammar','FIRST(S)  : { a b }'),('Nullable suffix FOLLOW','FOLLOW(A) : { $ b }'),('Left recursive grammar','FIRST(E)  : { a }')],
 '4_2': [('Valid sample','String Accepted'),('Invalid sample','String Rejected')],
 '4_3': [('Valid sample','String Accepted'),('Invalid sample','String Rejected')],
 '5_1': [('Division by zero','Error: division by zero')],
 '5_2': [('Equal precedence associativity','t1 = b - c'),('Repeated operators','t2 = t1 + d')],
 '5_3': [('Assembly output','IMUL BX'),('Assembly output','CWD')]
}
for id, cases in checks.items():
 rec=next(r for r in records if r['id']==id)
 for label, expected in cases:
  case=next((c for c in rec['runs'] if c['label']==label),None)
  if case is None or expected not in case['output']: failures.append(id+': '+label+' incorrect')
print('Report:',root/'PROGRAM_RUN_RESULTS.md')
if failures:
 print('FAILURES:',*failures,sep='\n'); raise SystemExit(1)
print('All builds and regression checks passed.')
