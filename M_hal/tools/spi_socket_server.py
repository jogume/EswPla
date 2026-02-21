#!/usr/bin/env python3
"""
SPI HAL Socket Server
A TCP socket server for feeding/receiving SPI data to/from the HAL socket implementation.
This server simulates an SPI device or test equipment for HIL (Hardware-in-the-Loop) testing.

Usage:
    python spi_socket_server.py [--host HOST] [--port PORT]

Author: EswPla HAL Team
Date: 2026-02-21
"""

import socket
import struct
import argparse
import threading
import time
import sys
from enum import IntEnum

class SpiMessageType(IntEnum):
    """SPI protocol message types"""
    INIT         = 0x01
    DEINIT       = 0x02
    TRANSFER     = 0x03
    SEND         = 0x04
    RECEIVE      = 0x05
    SET_CONFIG   = 0x06
    GET_STATUS   = 0x07
    RESPONSE     = 0x80

class SpiSocketServer:
    """SPI HAL Socket Server"""
    
    def __init__(self, host='127.0.0.1', port=9000):
        self.host = host
        self.port = port
        self.server_socket = None
        self.client_socket = None
        self.running = False
        self.spi_devices = {}  # Store device configurations
        
    def start(self):
        """Start the socket server"""
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        
        try:
            self.server_socket.bind((self.host, self.port))
            self.server_socket.listen(1)
            self.running = True
            print(f"[SPI-SERVER] Listening on {self.host}:{self.port}")
            
            while self.running:
                print("[SPI-SERVER] Waiting for connection...")
                self.client_socket, client_addr = self.server_socket.accept()
                print(f"[SPI-SERVER] Client connected from {client_addr}")
                
                # Handle client in a separate thread
                client_thread = threading.Thread(target=self.handle_client)
                client_thread.start()
                client_thread.join()
                
        except KeyboardInterrupt:
            print("\n[SPI-SERVER] Shutting down...")
        except Exception as e:
            print(f"[SPI-SERVER] ERROR: {e}")
        finally:
            self.stop()
    
    def stop(self):
        """Stop the server"""
        self.running = False
        if self.client_socket:
            self.client_socket.close()
        if self.server_socket:
            self.server_socket.close()
        print("[SPI-SERVER] Server stopped")
    
    def handle_client(self):
        """Handle client connection"""
        try:
            while self.running:
                # Receive message header (8 bytes)
                header_data = self.receive_all(8)
                if not header_data:
                    break
                
                msg_type, device_id, data_length, sequence = struct.unpack('<BBHI', header_data)
                
                print(f"[SPI-SERVER] RX: Type={hex(msg_type)}, Device={device_id}, "
                      f"Length={data_length}, Seq={sequence}")
                
                # Receive payload if present
                payload = None
                if data_length > 0:
                    payload = self.receive_all(data_length)
                    if not payload:
                        break
                
                # Process message
                response = self.process_message(msg_type, device_id, payload)
                
                # Send response
                if response is not None:
                    self.send_response(msg_type, device_id, sequence, response)
                    
        except Exception as e:
            print(f"[SPI-SERVER] Client error: {e}")
        finally:
            if self.client_socket:
                self.client_socket.close()
                self.client_socket = None
            print("[SPI-SERVER] Client disconnected")
    
    def receive_all(self, length):
        """Receive exact number of bytes"""
        data = b''
        while len(data) < length:
            chunk = self.client_socket.recv(length - len(data))
            if not chunk:
                return None
            data += chunk
        return data
    
    def send_response(self, msg_type, device_id, sequence, data):
        """Send response message"""
        response_type = SpiMessageType.RESPONSE
        data_length = len(data) if data else 0
        
        header = struct.pack('<BBHI', response_type, device_id, data_length, sequence)
        self.client_socket.sendall(header)
        
        if data:
            self.client_socket.sendall(data)
            
        print(f"[SPI-SERVER] TX: Response to seq={sequence}, length={data_length}")
    
    def process_message(self, msg_type, device_id, payload):
        """Process received message and generate response"""
        
        if msg_type == SpiMessageType.INIT:
            # Parse SPI configuration (8 bytes)
            if payload and len(payload) >= 8:
                baudrate, mode, bit_order, data_bits = struct.unpack('<IBBB', payload[:7])
                self.spi_devices[device_id] = {
                    'baudrate': baudrate,
                    'mode': mode,
                    'bit_order': bit_order,
                    'data_bits': data_bits,
                    'initialized': True
                }
                print(f"[SPI-SERVER] Device {device_id} initialized: "
                      f"{baudrate}Hz, mode={mode}, {data_bits}-bit")
            return b''  # Empty response = success
            
        elif msg_type == SpiMessageType.DEINIT:
            if device_id in self.spi_devices:
                del self.spi_devices[device_id]
                print(f"[SPI-SERVER] Device {device_id} deinitialized")
            return b''
            
        elif msg_type == SpiMessageType.TRANSFER:
            # Echo back the data (simulate SPI loopback)
            # In real application, this would communicate with actual device
            print(f"[SPI-SERVER] Transfer {len(payload)} bytes: {payload[:16].hex()}...")
            
            # Example: Process the data and return modified response
            response = self.simulate_spi_device_response(device_id, payload)
            return response
            
        elif msg_type == SpiMessageType.SEND:
            # Receive only - acknowledge
            print(f"[SPI-SERVER] Received {len(payload)} bytes: {payload[:16].hex()}...")
            return b''  # Acknowledge
            
        elif msg_type == SpiMessageType.RECEIVE:
            # Send data to client
            if payload and len(payload) >= 2:
                requested_length = struct.unpack('>H', payload[:2])[0]
                print(f"[SPI-SERVER] Requested {requested_length} bytes")
                
                # Generate test data
                response = self.generate_test_data(device_id, requested_length)
                return response
            return b''
            
        elif msg_type == SpiMessageType.SET_CONFIG:
            # Update configuration
            if payload and len(payload) >= 8:
                baudrate, mode, bit_order, data_bits = struct.unpack('<IBBB', payload[:7])
                if device_id in self.spi_devices:
                    self.spi_devices[device_id].update({
                        'baudrate': baudrate,
                        'mode': mode,
                        'bit_order': bit_order,
                        'data_bits': data_bits
                    })
                    print(f"[SPI-SERVER] Device {device_id} reconfigured")
            return b''
            
        else:
            print(f"[SPI-SERVER] Unknown message type: {hex(msg_type)}")
            return b''
    
    def simulate_spi_device_response(self, device_id, tx_data):
        """
        Simulate an SPI device response.
        Override this method to implement custom device behavior.
        """
        # Example: Echo with XOR modification
        response = bytes([b ^ 0x00 for b in tx_data])
        
        # Example: Simulate a specific device (e.g., accelerometer, ADC, etc.)
        # if device_id == 0:
        #     # Simulate accelerometer reading
        #     response = struct.pack('<HHH', 100, 200, 1024)  # X, Y, Z axes
        
        return response
    
    def generate_test_data(self, device_id, length):
        """
        Generate test data for receive operations.
        Override this method to provide custom test patterns.
        """
        # Generate incrementing pattern
        data = bytes([(i + device_id) % 256 for i in range(length)])
        
        # Alternative: Random data
        # import random
        # data = bytes([random.randint(0, 255) for _ in range(length)])
        
        return data


def main():
    """Main entry point"""
    parser = argparse.ArgumentParser(description='SPI HAL Socket Server')
    parser.add_argument('--host', default='127.0.0.1', 
                        help='Server host address (default: 127.0.0.1)')
    parser.add_argument('--port', type=int, default=9000, 
                        help='Server port (default: 9000)')
    
    args = parser.parse_args()
    
    print("=" * 60)
    print("SPI HAL Socket Server")
    print("=" * 60)
    print(f"Host: {args.host}")
    print(f"Port: {args.port}")
    print("Press Ctrl+C to stop")
    print("=" * 60)
    
    server = SpiSocketServer(host=args.host, port=args.port)
    server.start()


if __name__ == '__main__':
    main()
