import socket
import binascii

def byteToHex( byteStr ):
  """
  Convert a byte string to it's hex string representation e.g. for output.
  """

  # Uses list comprehension which is a fractionally faster implementation than
  # the alternative, more readable, implementation below
  #
  #    hex = []
  #    for aChar in byteStr:
  #        hex.append( "%02X " % ord( aChar ) )
  #
  #    return ''.join( hex ).strip()

  return ''.join( [ "%02X " % ord( x ) for x in byteStr ] ).strip()

messageHex = 'AA550086A2000201312063346361343233386130623932333832306463633530396136663735383439620D3139322E3136382E302E313530000130303030303000000000000038653963636134393530666534653265336461363539323736396233663033372343394146324136372D35453938423132412D33333637303642332D363344333044453155AA'

host = '0.0.0.0';socket.gethostname()
port = 12680

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
  s.connect((host, port))
except:
  print('Error')
else:
  while messageHex != 'q':
    s.sendall(binascii.unhexlify(messageHex))

    data = s.recv(1024)

    print('Received', repr(data))
    print('In Hex: {}', byteToHex(data))

    messageHex = raw_input('Insert next Hex Data: ')

s.close()

