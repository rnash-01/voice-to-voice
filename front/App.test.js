import App from './App.js';
import renderer from 'react-test-renderer';

test('returns React App', () => {

	const app = renderer.create(
		<App/>,
	);
	let tree = app.toJSON();

	// Not null?
	expect(app).not.toBe(null);

	// Check tree - should contain div
	console.log(tree);
	
	// Check tree. Should match Snapshot
	expect(tree).toMatchSnapshot();

	
});
